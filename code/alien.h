#pragma once
#include <raylib.h>


class Alien
{
public:

    Alien(int type, Vector2 position);
    void Update(int direction);
    void Draw() const;
    [[nodiscard]] int GetType() const;
    static void UnloadImages();
    [[nodiscard]] Rectangle GetRect() const;

    static Texture2D alienImages[3];
    int type{};
    Vector2 position{};
};
