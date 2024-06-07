#pragma once
#include "alien.h"
#include "obstacle.h"
#include "spaceship.h"

class Game
{
public:

    Game();
    void Draw() const;
    void Update(double deltaTime);
    void HandleInput(double deltaTime);
    void UnloadTextures() const;

private:

    void DeleteInactiveLasers();
    static std::vector<Obstacle> CreateObstacles();
    static std::vector<Alien> CreateAliens();
    void MoveAliens();

    Spaceship spaceship{};
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int aliensDirection;
};
