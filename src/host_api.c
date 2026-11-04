#include "host_api.h"
#include "machine_api.h"
#include <raylib.h>

void run_simulation() {
    InitWindow(displayParams.pixelsWidth, displayParams.pixelsHeight, "Space Invaders");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("It's space invaders...", 190, 200, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
}