#include <raylib.h>
#include "game.h"
#include "obstacle.h"

int main()
{
    constexpr Color grey = {29, 29, 27, 255};
    constexpr int screenWindth = 750;
    constexpr int screenHeight = 700;
    InitWindow(screenWindth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    double lastUpdate = GetTime();

    Game game;
    Obstacle obstacle = Obstacle({100, 100});

    while (!WindowShouldClose())
    {
        const double currentTime = GetTime();
        const double deltaTime = currentTime - lastUpdate;
        game.HandleInput(deltaTime);
        game.Update(deltaTime);

        BeginDrawing();
        ClearBackground(grey);

        game.Draw();
        obstacle.Draw();

        EndDrawing();
        lastUpdate = currentTime;
    }
    CloseWindow();
    return 0;
}
