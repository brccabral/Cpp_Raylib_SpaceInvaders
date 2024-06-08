#include <raylib.h>
#include "game.h"

int main()
{
    constexpr Color grey = {29, 29, 27, 255};
    constexpr Color yellow = {243, 216, 63, 255};

    constexpr int offset = 50;
    constexpr int screenWindth = 750;
    constexpr int screenHeight = 700;
    InitWindow(screenWindth + offset, screenHeight + 2 * offset, "Space Invaders");
    SetTargetFPS(60);

    double lastUpdate = GetTime();

    Game game;

    while (!WindowShouldClose())
    {
        const double currentTime = GetTime();
        const double deltaTime = currentTime - lastUpdate;
        game.HandleInput(deltaTime);
        game.Update(deltaTime);

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);

        game.Draw();

        EndDrawing();
        lastUpdate = currentTime;
    }

    // we must Unload all textures before CloseWindow()
    game.UnloadTextures();
    CloseWindow();
    return 0;
}
