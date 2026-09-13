#include <stdio.h>
#include <raylib.h>

int main() {
    printf("Starting the game...\n");
    InitWindow(750, 750, "Retro Snake");

    while(WindowShouldClose == false) {
        BeginDrawing(); // Creates a blank canvas to draw game objects on

        EndDrawing();
    }
    CloseWindow();
    return 0;
}