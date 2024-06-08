#include "game.h"

Game::Game()
{
    SetRandomSeed(GetTime());
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = GetTime();
    timeLastSpawnMysteryShip = GetTime();
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
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

    for (const auto &laser: alienLasers)
    {
        laser.Draw();
    }

    mystery_ship.Draw();
}

void Game::Update(const double deltaTime)
{
    for (auto &laser: spaceship.lasers)
    {
        laser.Update(deltaTime);
    }
    MoveAliens();
    AlienShootLaser();
    for (auto &laser: alienLasers)
    {
        laser.Update(deltaTime);
    }
    DeleteInactiveLasers();

    const double currentTime = GetTime();
    if (currentTime - timeLastSpawnMysteryShip > mysteryShipSpawnInterval)
    {
        mystery_ship.Spaw();
        timeLastSpawnMysteryShip = currentTime;
        mysteryShipSpawnInterval = GetRandomValue(10, 20);
    }
    mystery_ship.Update(deltaTime);
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

    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->active)
        {
            it = alienLasers.erase(it);
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

void Game::MoveAliens()
{
    for (auto &alien: aliens)
    {
        if (alien.position.x + Alien::alienImages[alien.type - 1].width > GetScreenWidth())
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 0)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }

        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(const int distance)
{
    for (auto &alien: aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    const double currentTime = GetTime();
    if (currentTime - timeLastAlienFired > alienLaserShootInterval && !aliens.empty())
    {
        const int randomAlien = GetRandomValue(0, aliens.size() - 1);
        const Alien &alien = aliens[randomAlien];
        const float x = alien.position.x + Alien::alienImages[alien.type - 1].width / 2.0f;
        const float y = alien.position.y + Alien::alienImages[alien.type - 1].height;
        alienLasers.push_back(Laser({x, y}, 426));
        timeLastAlienFired = currentTime;
    }
}

void Game::UnloadTextures() const
{
    spaceship.UnloadImage();
    Alien::UnloadImages();
    mystery_ship.UnloadImage();
}
