#include "laser.h"

Laser::Laser(const Vector2 position, const int speed) : position(position), speed(speed)
{
    color = {243, 216, 63, 255};
    size = {4, 15};
}

void Laser::Update(const double deltaTime)
{
    position.y += speed * deltaTime;
}

void Laser::Draw() const
{
    DrawRectangleV(position, size, color);
}
