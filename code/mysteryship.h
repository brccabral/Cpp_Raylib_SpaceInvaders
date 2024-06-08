#pragma once
#include <raylib.h>


class MysteryShip
{
public:

    MysteryShip();
    void Update(double deltaTime);
    void Draw() const;
    void Spaw();
    void UnloadImage() const;
    bool alive;

private:

    Vector2 position{};
    Texture2D image{};
    int speed{};
};
