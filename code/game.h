#pragma once
#include "alien.h"
#include "obstacle.h"
#include "spaceship.h"

class Game
{
public:

    Game();
    ~Game();
    void Draw() const;
    void Update(double deltaTime);
    void HandleInput(double deltaTime);

private:

    void DeleteInactiveLasers();
    static std::vector<Obstacle> CreateObstacles();
    static std::vector<Alien> CreateAliens();

    Spaceship spaceship{};
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
};
