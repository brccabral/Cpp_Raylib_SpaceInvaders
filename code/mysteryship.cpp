#include "mysteryship.h"
MysteryShip::MysteryShip()
{
    image = LoadTexture("resources/Graphics/mystery.png");
    alive = false;
    speed = 213;
}

void MysteryShip::UnloadImage() const
{
    UnloadTexture(image);
}

Rectangle MysteryShip::GetRect() const
{
    if (alive)
    {
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else
    {
        return {position.x, position.y, 0, 0};
    }
}

void MysteryShip::Update(const double deltaTime)
{
    if (alive)
    {
        position.x += speed * deltaTime;
        if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25)
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
        position.x = 25;
        speed = 213;
    }
    else
    {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -213;
    }
    alive = true;
}
