#pragma once
#include <raylib.h>

class Spaceship
{
public:

    Spaceship();
    ~Spaceship();
    void Draw() const;
    void MoveLeft();
    void MoveRight();
    void FireLaser();

private:

    Texture2D image{};
    Vector2 position{};
};
