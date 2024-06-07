#include "alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(const int type, const Vector2 position) : type(type), position(position)
{
    if (alienImages[type - 1].id == 0)
    {
        switch (type)
        {
            case 1:
            {
                alienImages[0] = LoadTexture("resources/Graphics/alien_1.png");
                break;
            }
            case 2:
            {
                alienImages[1] = LoadTexture("resources/Graphics/alien_2.png");
                break;
            }
            case 3:
            {
                alienImages[2] = LoadTexture("resources/Graphics/alien_3.png");
                break;
            }
            default:
            {
                alienImages[type - 1] = LoadTexture("resources/Graphics/alien_1.png");
                break;
            }
        }
    }
}

Alien::~Alien()
{}

void Alien::Draw() const
{
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

int Alien::GetType() const
{
    return type;
}
