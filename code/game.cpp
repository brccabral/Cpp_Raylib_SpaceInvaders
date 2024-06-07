#include "game.h"

Game::Game()
{}

Game::~Game()
{}

void Game::Draw() const
{
    spaceship.Draw();
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
}
