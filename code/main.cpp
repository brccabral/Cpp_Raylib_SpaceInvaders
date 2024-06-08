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

    const Font font = LoadFontEx("resources/Font/monogram.ttf", 64, nullptr, 0);
    const Texture2D spaceshipImage = LoadTexture("resources/Graphics/spaceship.png");

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
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        if (game.isRunning)
        {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        float x = 50.0f;
        for (int i = 0; i < game.lives; ++i)
        {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += spaceshipImage.width + 5;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        DrawTextEx(font, TextFormat("%05i", game.score), {50, 40}, 34, 2, yellow);

        game.Draw();

        EndDrawing();
        lastUpdate = currentTime;
    }

    // we must Unload all textures before CloseWindow()
    game.UnloadTextures();
    UnloadTexture(spaceshipImage);
    CloseWindow();
    return 0;
}
