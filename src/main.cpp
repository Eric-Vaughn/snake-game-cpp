#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std; // Tutorial has this, I know it's not best practice

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            // Rectangle struct wants floats not int
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update()
    {
        body.pop_back();
        body.push_front(body[0] + direction);
    }
};

class Food
{

public:
    Vector2 position;
    Texture2D texture;

    // Constructor
    Food()
    {
        Image image = LoadImage("src/resources/graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    // Destructor
    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
};

int main()
{

    cout << "Starting the game..." << endl;
    // printf("Starting the game...\n");
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake"); // Create game window
    SetTargetFPS(60);

    Food food = Food();
    Snake snake = Snake();

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing(); // Creates a blank canvas to draw game objects on

        snake.Update();

        // Drawing
        ClearBackground(green);
        food.Draw();
        snake.Draw();

        EndDrawing(); // MUST end drawing
    }

    CloseWindow(); // MUST destory game window
    return 0;
}