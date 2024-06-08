#include "spaceship.h"

Spaceship::Spaceship()
{
    image = LoadTexture("resources/Graphics/spaceship.png");
    position = {(GetScreenWidth() - image.width) / 2.0f, (float) (GetScreenHeight() - image.height)};
    lastFireTime = GetTime();
    fireRate = 0.35;
}

void Spaceship::Draw() const
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft(const double deltaTime)
{
    position.x -= speed * deltaTime;
    if (position.x < 0)
    {
        position.x = 0;
    }
}

void Spaceship::MoveRight(const double deltaTime)
{
    position.x += speed * deltaTime;
    if (position.x > GetScreenWidth() - image.width)
    {
        position.x = GetScreenWidth() - image.width;
    }
}

void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime >= fireRate)
    {
        lasers.push_back(Laser({position.x + image.width / 2.0f - 2, position.y}, -426));
        lastFireTime = GetTime();
    }
}

void Spaceship::UnloadImage() const
{
    UnloadTexture(image);
}

Rectangle Spaceship::GetRect() const
{
    return {position.x, position.y, float(image.width), float(image.height)};
}
