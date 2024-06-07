#include "game.h"

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
}

void Game::Draw() const
{
    spaceship.Draw();

    for (const Laser &laser: spaceship.lasers)
    {
        laser.Draw();
    }

    for (const auto &obstacle: obstacles)
    {
        obstacle.Draw();
    }

    for (const auto &alien: aliens)
    {
        alien.Draw();
    }
}

void Game::Update(const double deltaTime)
{
    for (auto &laser: spaceship.lasers)
    {
        laser.Update(deltaTime);
    }
    DeleteInactiveLasers();
}

void Game::HandleInput(const double deltaTime)
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft(deltaTime);
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight(deltaTime);
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    const int obstaclesWidth = Obstacle::grid[0].size() * 3;
    const float gap = (GetScreenWidth() - (4 * obstaclesWidth)) / 5.0f;
    std::vector<Obstacle> newObstacles;
    for (int i = 0; i < 4; ++i)
    {
        const float offset_x = (i + 1) * gap + i * obstaclesWidth;
        newObstacles.push_back(Obstacle({offset_x, (float) (GetScreenHeight() - 100)}));
    }
    return newObstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> newAliens;
    for (int row = 0; row < 5; ++row)
    {
        for (int column = 0; column < 11; ++column)
        {
            const float x = column * 55 + 75;
            const float y = row * 55 + 110;

            int alienType;
            if (row == 0)
            {
                alienType = 3;
            }
            else if (row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }
            newAliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return newAliens;
}

void Game::UnloadTextures() const
{
    spaceship.UnloadImage();
    Alien::UnloadImages();
}
