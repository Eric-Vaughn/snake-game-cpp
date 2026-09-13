#include <stdio.h>
#include <raylib.h>

int main() {
    printf("Starting the game...\n");
    InitWindow(750, 750, "Retro Snake"); // Create game window
    SetTargetFPS(60);

    // Main game loop
    while(!WindowShouldClose()) {
        BeginDrawing(); // Creates a blank canvas to draw game objects on

        EndDrawing(); // MUST end drawing
    }

    CloseWindow(); // MUST destory game window
    return 0;
}