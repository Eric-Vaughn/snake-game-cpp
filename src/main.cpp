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

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            true;
        }
    }

    return false;
}

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
    bool addSegment = false;

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
        body.push_front(Vector2Add(body[0], direction));
        if (addSegment)
        {
            addSegment = false;
        }
        else
        {
            body.pop_back();
        }
    }

    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};

class Food
{

public:
    Vector2 position;
    Texture2D texture;

    // Constructor
    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("src/resources/graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
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

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 postion = GenerateRandomCell();
        while (ElementInDeque(position, snakeBody))
        {
            postion = GenerateRandomCell();
        }
        return postion;
    }
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);

    void Draw()
    {
        snake.Draw();
        food.Draw();
    }

    void Update()
    {
        snake.Update();
        CheckCollisionWithFood();
    }

    void CheckCollisionWithFood()
    {
        // Check if snake's head is at food's position
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
        }
    }

    void CheckCollisionWithEdge()
    {
        // Right or left edge
        if (snake.body[0].x == cellCount || snake.body[0].x == -1)
        {
            GameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
    }
};

int main()
{

    cout << "Starting the game..." << endl;
    // printf("Starting the game...\n");
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake"); // Create game window
    SetTargetFPS(60);

    Game game = Game();

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing(); // Creates a blank canvas to draw game objects on

        if (eventTriggered(0.2))
        {
            game.Update();
        }

        // Player movement
        /* TODO: BUG
        If two keys are pressed quickly, the snake can
        "turn around" in place
        */
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) // UP
        {
            game.snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) // DOWN
        {
            game.snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) // LEFT
        {
            game.snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) // RIGHT
        {
            game.snake.direction = {1, 0};
        }

        // Drawing
        ClearBackground(green);
        game.Draw();

        EndDrawing(); // MUST end drawing
    }

    CloseWindow(); // MUST destory game window
    return 0;
}