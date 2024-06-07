#pragma once
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
    Spaceship spaceship{};
};
