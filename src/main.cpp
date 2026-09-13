#include <iostream>
#include <raylib.h>

using namespace std; // Tutorial has this, I know it's not best practice

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food {
    public:
        Vector2 position = {5, 6};

        void Draw() {
            DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
        }

};

int main() {
    
    cout << "Starting the game..." << endl;
    // printf("Starting the game...\n");
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake"); // Create game window
    SetTargetFPS(60);

    Food food = Food();

    // Main game loop
    while(!WindowShouldClose()) {
        BeginDrawing(); // Creates a blank canvas to draw game objects on

        // Drawing
        ClearBackground(green);
        food.Draw();

        EndDrawing(); // MUST end drawing
    }

    CloseWindow(); // MUST destory game window
    return 0;
}