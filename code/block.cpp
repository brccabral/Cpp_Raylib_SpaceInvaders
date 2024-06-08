#include "block.h"

Block::Block(const Vector2 position) : position(position), size({3, 3}), color({243, 216, 63, 255})
{}

void Block::Draw() const
{
    DrawRectangleV(position, size, color);
}

Rectangle Block::GetRect() const
{
    return {position.x, position.y, size.x, size.y};
}
