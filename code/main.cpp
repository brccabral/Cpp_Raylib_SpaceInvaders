#include <raylib.h>
#include "game.h"
#include "laser.h"

int main()
{
    constexpr Color grey = {29, 29, 27, 255};
    constexpr int screenWindth = 750;
    constexpr int screenHeight = 700;
    InitWindow(screenWindth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    double lastUpdate = GetTime();

    Game game;
    Laser laser = Laser({100, 100}, 500);

    while (!WindowShouldClose())
    {
        const double currentTime = GetTime();
        const double deltaTime = currentTime - lastUpdate;
        game.HandleInput(deltaTime);
        laser.Update(deltaTime);

        BeginDrawing();
        ClearBackground(grey);

        game.Draw();
        laser.Draw();

        EndDrawing();
        lastUpdate = currentTime;
    }
    CloseWindow();
    return 0;
}
