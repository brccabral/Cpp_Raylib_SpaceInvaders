#include "alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(const int type, const Vector2 position) : type(type), position(position)
{
    if (type < 1 || type > 3)
    {
        this->type = 1;
    }
    if (alienImages[this->type - 1].id == 0)
    {
        switch (this->type)
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
                alienImages[0] = LoadTexture("resources/Graphics/alien_1.png");
                break;
            }
        }
    }
}

void Alien::Update(const int direction)
{
    position.x += direction;
}

void Alien::Draw() const
{
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

int Alien::GetType() const
{
    return type;
}

void Alien::UnloadImages()
{
    for (const auto &alienImage: Alien::alienImages)
    {
        UnloadTexture(alienImage);
    }
}
