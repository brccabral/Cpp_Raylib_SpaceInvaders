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
        if (position.y > GetScreenHeight() - 100 || position.y < 25)
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

Rectangle Laser::GetRect() const
{
    return {position.x, position.y, size.x, size.y};
}
