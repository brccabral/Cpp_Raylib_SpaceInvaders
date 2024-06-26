#include "game.h"

#include <fstream>
#include <iostream>

Game::Game()
{
    SetRandomSeed(GetTime());
    InitGame();
    music = LoadMusicStream("resources/Sounds/music.ogg");
    PlayMusicStream(music);
    explosionSound = LoadSound("resources/Sounds/explosion.ogg");
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
    if (!isRunning)
    {
        return;
    }
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

    CheckForCollisions();
}

void Game::HandleInput(const double deltaTime)
{
    if (!isRunning)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
        return;
    }
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
        newObstacles.push_back(Obstacle({offset_x, (float) (GetScreenHeight() - 200)}));
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
        if (alien.position.x + Alien::alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
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

void Game::CheckForCollisions()
{
    for (auto &laser: spaceship.lasers)
    {
        // spaceship laser against aliens
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
            {
                if (it->type == 1)
                {
                    score += 100;
                }
                else if (it->type == 2)
                {
                    score += 200;
                }
                else if (it->type == 3)
                {
                    score += 300;
                }
                it = aliens.erase(it);
                laser.active = false;
                CheckForHighscore();
                PlaySound(explosionSound);
            }
            else
            {
                ++it;
            }
        }

        // spaceship laser against obstacles
        for (auto &obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    ++it;
                }
            }
        }

        // spaceship laser against mystery ship
        if (CheckCollisionRecs(mystery_ship.GetRect(), laser.GetRect()))
        {
            mystery_ship.alive = false;
            laser.active = false;
            score += 500;
            CheckForHighscore();
            PlaySound(explosionSound);
        }
    }

    for (auto &laser: alienLasers)
    {
        // aliens laser against obstacles
        for (auto &obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    ++it;
                }
            }
        }

        // aliens laser against spaceship
        if (CheckCollisionRecs(laser.GetRect(), spaceship.GetRect()))
        {
            laser.active = false;
            --lives;
            if (lives < 1)
            {
                GameOver();
            }
        }
    }

    // Alien against obstacle
    for (auto &alien: aliens)
    {
        for (auto &obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRect(), alien.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        // aliens against spaceship
        if (CheckCollisionRecs(alien.GetRect(), spaceship.GetRect()))
        {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    isRunning = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = GetTime();
    timeLastSpawnMysteryShip = GetTime();
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    isRunning = true;
    score = 0;
    highScore = LoadHighscoreFromFile();
}

void Game::CheckForHighscore()
{
    if (score > highScore)
    {
        highScore = score;
        SaveHighscoreToFile(highScore);
    }
}

void Game::SaveHighscoreToFile(const int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open())
    {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file\n";
    }
}

int Game::LoadHighscoreFromFile()
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open())
    {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to load highscore from file\n";
    }
    return loadedHighscore;
}

void Game::UnloadTextures() const
{
    spaceship.UnloadImage();
    Alien::UnloadImages();
    mystery_ship.UnloadImage();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}
