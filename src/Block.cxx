#include "Block.h"

Block::Block()
{
}

Block::Block(int x, int y, const BlockTemplate& blockTemplate)
    : x(x), y(y), bufX(x), bufY(y), blockTemplate(blockTemplate)
{
}

void Block::updatePos()
{
    if (!locked)
    {
        x = bufX;
        y = bufY;
    }
}

void Block::setX(int x)
{
    bufX = x;
    updatePos();
}

void Block::setY(int y)
{
    bufY = y;
    updatePos();
}

void Block::changeX(int x)
{
    bufX += x;
    updatePos();
}

void Block::changeY(int y)
{
    bufY += y;
    updatePos();
}

const templateData_t& Block::getTemplateData() const
{
    return blockTemplate.templateData;
}

const glm::vec3& Block::getColor() const
{
    return blockTemplate.color;
}

int Block::getX() const
{
    return x;
}

int Block::getY() const
{
    return y;
}

size_t Block::getWidth() const
{
    return blockTemplate.templateData[0].size();
}

size_t Block::getHeight() const
{
    return blockTemplate.templateData.size();
}

bool Block::getLocked() const
{
    return locked;
}

void Block::lock()
{
    locked = true;
}

void Block::unlock()
{
    locked = false;
    updatePos();
}