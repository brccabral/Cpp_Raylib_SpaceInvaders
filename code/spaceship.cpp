#include "spaceship.h"

Spaceship::Spaceship()
{
    image = LoadTexture("resources/Graphics/spaceship.png");
    laserSound = LoadSound("resources/Sounds/laser.ogg");
    Reset();
}

void Spaceship::Draw() const
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft(const double deltaTime)
{
    position.x -= speed * deltaTime;
    if (position.x < 25)
    {
        position.x = 25;
    }
}

void Spaceship::MoveRight(const double deltaTime)
{
    position.x += speed * deltaTime;
    if (position.x > GetScreenWidth() - image.width - 25)
    {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime >= fireRate)
    {
        lasers.push_back(Laser({position.x + image.width / 2.0f - 2, position.y}, -426));
        lastFireTime = GetTime();
        PlaySound(laserSound);
    }
}

void Spaceship::UnloadImage() const
{
    UnloadTexture(image);
    UnloadSound(laserSound);
}

Rectangle Spaceship::GetRect() const
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
    position = {(GetScreenWidth() - image.width) / 2.0f, (float) (GetScreenHeight() - image.height - 100)};
    lastFireTime = GetTime();
    fireRate = 0.35;
    lasers.clear();
}
