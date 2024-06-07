#include "game.h"

Game::Game()
{}

Game::~Game()
{}

void Game::Draw() const
{
    spaceship.Draw();

    for (const Laser &laser: spaceship.lasers)
    {
        laser.Draw();
    }
}

void Game::Update(const double deltaTime)
{
    for (auto &laser: spaceship.lasers)
    {
        laser.Update(deltaTime);
    }
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
