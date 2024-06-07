#include "game.h"

Game::Game()
{
    obstacles = CreateObstacles();
}

Game::~Game()
{}

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
