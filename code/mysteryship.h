#pragma once
#include <raylib.h>


class MysteryShip
{
public:

    MysteryShip();
    ~MysteryShip();
    void Update(double deltaTime);
    void Draw() const;
    void Spaw();
    bool alive;

private:

    Vector2 position{};
    Texture2D image{};
    int speed{};
};
