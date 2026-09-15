#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std; // Tutorial has this, I know it's not best practice

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0; // Time at which last update of the Snake occured

bool eventTriggered(double interval)
{
    double currentTime = GetTime(); // In seconds
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

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

class Game
{
public:
    Food food = Food();
    Snake snake = Snake();

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        snake.Update();
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

        if (eventTriggered(0.2))
        {
            snake.Update();
        }

        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1) // UP
        {
            snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1) // DOWN
        {
            snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1) // LEFT
        {
            snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1) // RIGHT
        {
            snake.direction = {1, 0};
        }
        // Drawing
        ClearBackground(green);
        food.Draw();
        snake.Draw();

        EndDrawing(); // MUST end drawing
    }

    CloseWindow(); // MUST destory game window
    return 0;
}