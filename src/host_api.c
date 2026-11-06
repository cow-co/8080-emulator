#include "host_api.h"
#include "machine_api.h"
#include <raylib.h>
#include <stddef.h>


bool generate_pixel_value(const uint8_t x, const uint8_t y, const uint8_t* const buffer) {
    const uint8_t pixelOffset = x * displayParams.pixelsHeight + y;    // eg. 256
    const bool* const bufferAsBits = (bool*)buffer;
    return bufferAsBits[pixelOffset];
}

void run_simulation() {
    load_rom();
    
    InitWindow(displayParams.pixelsWidth, displayParams.pixelsHeight, "Space Invaders");
    InitAudioDevice();

    Sound sfxes[9] = {};
    
    for (size_t i = 0; i < sizeof(sfxFiles) / sizeof(sfxFiles[0]); ++i) {
        sfxes[i] = LoadSound(sfxFiles[i]);
    }

    Image displayImage = GenImageColor(displayParams.pixelsWidth, displayParams.pixelsHeight, BLACK);
    Texture displayTexture = LoadTextureFromImage(displayImage);
    Color pixColourOn = WHITE;
    Color pixColourOff = BLACK;

    while(!WindowShouldClose()) {
        // Iterate through the program
        run_machine();
        
        // Render
        const uint8_t* const framebuffer = graphics_state();
        for (size_t x = 0; x < displayParams.pixelsWidth; ++x) {
            for (size_t y = 0; y < displayParams.pixelsHeight; ++y) {
                const bool pixelValue = generate_pixel_value(x, y, framebuffer);
                ImageDrawPixel(&displayImage, x, y, pixelValue ? pixColourOn : pixColourOff);
            }
        }
        UpdateTexture(displayTexture, displayImage.data);
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(displayTexture, 0, 0, WHITE);
        EndDrawing();

        // Sounds
        queued_sfx();
        if (ampEnable && GetMasterVolume() < 0.5) {
            SetMasterVolume(0.5);
        } else if (!ampEnable && GetMasterVolume() > 0.0) {
            SetMasterVolume(0.0);
        }

        for (size_t i = 0; i < sizeof(sfxFiles) / sizeof(sfxFiles[0]); ++i) {
            if (sfxStates[i]) {
                PlaySound(sfxes[i]);
            }
        }

        // Input
        // Unset any released keys
        if (IsKeyUp(KEY_ENTER)) {
            key_release(P1_START);
        }
        if (IsKeyUp(KEY_D)) {
            key_release(P1_RIGHT);
        }
        if (IsKeyUp(KEY_A)) {
            key_release(P1_LEFT);
        }
        if (IsKeyUp(KEY_SPACE)) {
            key_release(P1_SHOOT);
        }
        if (IsKeyUp(KEY_KP_ENTER)) {
            key_release(P2_START);
        }
        if (IsKeyUp(KEY_RIGHT)) {
            key_release(P2_RIGHT);
        }
        if (IsKeyUp(KEY_LEFT)) {
            key_release(P2_LEFT);
        }
        if (IsKeyUp(KEY_KP_0)) {
            key_release(P2_SHOOT);
        }
        if(IsKeyUp(KEY_PAUSE)) {
            key_release(COIN_INSERT);
        }

        // Set any pressed keys
        if (IsKeyDown(KEY_ENTER)) {
            key_press(P1_START);
        }
        if (IsKeyDown(KEY_D)) {
            key_press(P1_RIGHT);
        }
        if (IsKeyDown(KEY_A)) {
            key_press(P1_LEFT);
        }
        if (IsKeyDown(KEY_SPACE)) {
            key_press(P1_SHOOT);
        }

        if (IsKeyDown(KEY_RIGHT)) {
            key_press(P2_RIGHT);
        }
        if (IsKeyDown(KEY_KP_ENTER)) {
            key_press(P2_START);
        }
        if (IsKeyDown(KEY_LEFT)) {
            key_press(P2_LEFT);
        }
        if (IsKeyDown(KEY_KP_0)) {
            key_press(P2_SHOOT);
        }
        if(IsKeyDown(KEY_PAUSE)) {
            key_press(COIN_INSERT);
        }
    }

    UnloadTexture(displayTexture);
    UnloadImage(displayImage);
    for (size_t i = 0; i < sizeof(sfxFiles) / sizeof(sfxFiles[0]); ++i) {
        UnloadSound(sfxes[i]);
    }
    CloseAudioDevice();
    CloseWindow();
}