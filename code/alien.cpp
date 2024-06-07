#include "alien.h"

Alien::Alien(const int type, const Vector2 position) : type(type), position(position)
{
    switch (type)
    {
        case 1:
        {
            image = LoadTexture("resources/Graphics/alien_1.png");
            break;
        }
        case 2:
        {
            image = LoadTexture("resources/Graphics/alien_2.png");
            break;
        }
        case 3:
        {
            image = LoadTexture("resources/Graphics/alien_3.png");
            break;
        }
        default:
        {
            image = LoadTexture("resources/Graphics/alien_1.png");
            break;
        }
    }
}

Alien::~Alien()
{
    UnloadTexture(image);
}

void Alien::Draw() const
{
    DrawTextureV(image, position, WHITE);
}

int Alien::GetType() const
{
    return type;
}
