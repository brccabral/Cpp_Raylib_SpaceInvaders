#include <raylib.h>

int main()
{
    constexpr Color grey = {29, 29, 27, 255};
    constexpr int screenWindth = 750;
    constexpr int screenHeight = 700;
    InitWindow(screenWindth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
