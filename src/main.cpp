#include "raylib.h"
#include "raymath.h"


int main()
{
    InitWindow(800, 450, "Hello World");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MAROON);
        DrawText("Hello, World!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }   
    
    CloseWindow();
    return 0;
}