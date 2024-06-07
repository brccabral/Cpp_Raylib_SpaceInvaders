#pragma once
#include "spaceship.h"

class Game
{
public:

    Game();
    ~Game();
    void Draw() const;
    void Update();
    void HandleInput();

private:

    Spaceship spaceship{};
};
