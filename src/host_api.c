#include "host_api.h"
#include "machine_api.h"
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>


bool generate_pixel_value(const uint8_t x, const uint8_t y, const uint8_t* const buffer) {
    const uint8_t pixelOffset = x * displayParams.pixelsHeight + y;    // eg. 256
    const bool* const bufferAsBits = (bool*)buffer;
    return bufferAsBits[pixelOffset];
}


void run_simulation() {
    InitWindow(displayParams.pixelsWidth, displayParams.pixelsHeight, "Space Invaders");
    InitAudioDevice();
    SetTargetFPS(60);

    Music musics[16] = {};    // Let's just allow a max of 16 audio files
    for (size_t i = 0; i < sizeof(sfx_files) / sizeof(sfx_files[0]); ++i) {
        musics[i] = LoadMusicStream(sfx_files[i]);
        musics[i].looping = false;
    }
    SFX_TYPE currentMusic = SOUND_NONE;

    Image displayImage = GenImageColor(displayParams.pixelsWidth, displayParams.pixelsHeight, BLACK);
    Texture displayTexture = LoadTextureFromImage(displayImage);
    Color pixColourOn = WHITE;
    Color pixColourOff = BLACK;

    while(!WindowShouldClose()) {
        run_machine();
        
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


        const SFX_TYPE sfx = queued_sfx();
        if (sfx == SOUND_AMP_ENABLE) {
            SetMasterVolume(0.);
        } else {
            SetMasterVolume(0.8);
        }

        // XXX DO we need to manually unset the bit on the output port once we've read it?
        if (
            sfx != SOUND_NONE 
            && sfx != SOUND_EXTENDED_PLAY
            && sfx != SOUND_AMP_ENABLE
        ) {
            PlayMusicStream(musics[sfx]);
        }

        // TODO Add the P2 keys and the Coin keys
        // Unset any released keys
        if (IsKeyUp(KEY_RIGHT)) {
            key_release(P1_RIGHT);
        }
        if (IsKeyUp(KEY_LEFT)) {
            key_release(P1_LEFT);
        }
        if (IsKeyUp(KEY_SPACE)) {
            key_release(P1_SHOOT);
        }

        // Set any pressed keys
        if (IsKeyDown(KEY_RIGHT)) {
            key_press(P1_RIGHT);
        }
        if (IsKeyDown(KEY_LEFT)) {
            key_press(P1_LEFT);
        }
        if (IsKeyDown(KEY_SPACE)) {
            key_press(P1_SHOOT);
        }
    }

    UnloadTexture(displayTexture);
    UnloadImage(displayImage);
    for (size_t i = 0; i < sizeof(sfx_files) / sizeof(sfx_files[0]); ++i) {
        UnloadMusicStream(musics[i]);
    }
    CloseWindow();
}