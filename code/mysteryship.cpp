#include "mysteryship.h"
MysteryShip::MysteryShip()
{
    image = LoadTexture("resources/Graphics/mystery.png");
    alive = false;
    speed = 213;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

void MysteryShip::Update(const double deltaTime)
{
    if (alive)
    {
        position.x += speed * deltaTime;
        if (position.x > GetScreenWidth() - image.width || position.x < 0)
        {
            alive = false;
        }
    }
}

void MysteryShip::Draw() const
{
    if (alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}

void MysteryShip::Spaw()
{
    position.y = 90;
    if (GetRandomValue(0, 1))
    {
        position.x = 0;
        speed = 213;
    }
    else
    {
        position.x = GetScreenWidth() - image.width;
        speed = -213;
    }
    alive = true;
}
