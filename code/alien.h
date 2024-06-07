#pragma once
#include <raylib.h>


class Alien
{
public:

    Alien(int type, Vector2 position);
    ~Alien();
    void Update();
    void Draw() const;
    [[nodiscard]] int GetType() const;

    static Texture2D alienImages[3];
    int type{};
    Vector2 position{};
};
