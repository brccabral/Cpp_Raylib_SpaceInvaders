#pragma once
#include <raylib.h>

class Block
{
public:

    explicit Block(Vector2 position);
    void Draw() const;

private:

    Vector2 position{};
    Vector2 size;
    Color color;
};
