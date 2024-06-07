#pragma once
#include <raylib.h>

class Spaceship
{
public:

    Spaceship();
    ~Spaceship();
    void Draw() const;
    void MoveLeft(double deltaTime);
    void MoveRight(double deltaTime);
    void FireLaser();

private:

    Texture2D image{};
    Vector2 position{};

    unsigned int speed = 500;
};
