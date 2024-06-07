#include "spaceship.h"

Spaceship::Spaceship()
{
    image = LoadTexture("resources/Graphics/spaceship.png");
    position = {(GetScreenWidth() - image.width) / 2.0f, (float) (GetScreenHeight() - image.height)};
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}
void Spaceship::Draw() const
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft(const double deltaTime)
{
    position.x -= speed * deltaTime;
}

void Spaceship::MoveRight(const double deltaTime)
{
    position.x += speed * deltaTime;
}
