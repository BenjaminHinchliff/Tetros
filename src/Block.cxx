#include "Block.h"

#include <iostream>

Block::Block()
{
}

Block::Block(int x, int y, const BlockTemplate& blockTemplate)
    : x(x - blockTemplate.templateData[0].size() / 2), y(y),
    bufX(this->x), bufY(this->y),
    templateData(blockTemplate.templateData),
    templateBuf(templateData),
    color(blockTemplate.color)
{
}

void Block::updateData()
{
    if (!locked)
    {
        x = bufX;
        y = bufY;
        templateData = templateBuf;
    }
}

void Block::setX(int x)
{
    bufX = x;
    updateData();
}

void Block::setY(int y)
{
    bufY = y;
    updateData();
}

void Block::changeX(int x)
{
    bufX += x;
    updateData();
}

void Block::changeY(int y)
{
    bufY += y;
    updateData();
}

void Block::rotate()
{
    const templateData_t& unrotated = templateBuf;
    templateData_t rotatedTemplate = {};
    for (size_t x = 0; x < unrotated[0].size(); ++x)
    {
        std::vector<bool> row;
        for (int y = unrotated.size() - 1; y >= 0; --y)
        {
            row.push_back(unrotated[y][x]);
        }
        rotatedTemplate.push_back(row);
    }

    templateBuf = std::move(rotatedTemplate);
    updateData();
}
void Block::unrotate()
{
    // lazy but DRY...
    for (size_t i = 0; i < 3; ++i)
    {
        rotate();
    }
}

const templateData_t& Block::getTemplateData() const
{
    return templateData;
}

const glm::vec3& Block::getColor() const
{
    return color;
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
    return templateData[0].size();
}

size_t Block::getHeight() const
{
    return templateData.size();
}

bool Block::getLocked() const
{
    return locked;
}

int Block::getBufX() const
{
    return bufX;
}

int Block::getBufY() const
{
    return bufY;
}

void Block::lock()
{
    locked = true;
}

void Block::unlock()
{
    locked = false;
    updateData();
}