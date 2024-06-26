#pragma once
#include <raylib.h>

class Laser
{
public:

    Laser(Vector2 position, int speed);
    void Update(double deltaTime);
    void Draw() const;
    bool active{};
    [[nodiscard]] Rectangle GetRect() const;

private:

    Vector2 position;
    int speed;
    Color color{};
    Vector2 size{};
};
