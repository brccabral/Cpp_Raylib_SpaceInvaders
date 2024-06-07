#include "spaceship.h"

Spaceship::Spaceship()
{
    image = LoadTexture("resources/Graphics/spaceship.png");
    position = {100, 100};
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}
void Spaceship::Draw() const
{
    DrawTextureV(image, position, WHITE);
}
