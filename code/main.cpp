#include <raylib.h>
#include "game.h"

int main()
{
    constexpr Color grey = {29, 29, 27, 255};
    constexpr int screenWindth = 750;
    constexpr int screenHeight = 700;
    InitWindow(screenWindth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);

        game.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
