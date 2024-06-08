#pragma once
#include <raylib.h>
#include <vector>
#include "laser.h"

class Spaceship
{
public:

    Spaceship();
    void Draw() const;
    void MoveLeft(double deltaTime);
    void MoveRight(double deltaTime);
    void FireLaser();
    void UnloadImage() const;
    std::vector<Laser> lasers;
    Rectangle GetRect() const;

private:

    Texture2D image{};
    Vector2 position{};

    unsigned int speed = 500;
    double lastFireTime{};
    double fireRate{};
};
