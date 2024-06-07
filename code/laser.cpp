#include "laser.h"

Laser::Laser(const Vector2 position, const int speed) : position(position), speed(speed)
{
    color = {243, 216, 63, 255};
    size = {4, 15};
    active = true;
}

void Laser::Update(const double deltaTime)
{
    position.y += speed * deltaTime;
    if (active)
    {
        if (position.y > GetScreenHeight() || position.y < 0)
        {
            active = false;
        }
    }
}

void Laser::Draw() const
{
    if (active)
    {
        DrawRectangleV(position, size, color);
    }
}
