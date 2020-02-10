#include "Grid.h"

#include <iostream>

Grid::Grid()
{
}

Grid::Grid(int width, int height, float blockSize, glm::mat4 projection, float xOff)
    : grid(height, std::vector(width, blank)), square(xOff, 0, blockSize, glm::vec3(1.0f, 0.0f, 0.0f), projection)
{
}

void Grid::setNodeColor(int x, int y, const glm::vec3& color)
{
    grid[y][x] = color;
}

void Grid::modBlockBase(int offX, int offY, const templateData_t& data, const glm::vec3& color)
{
    for (size_t y = 0; y < data.size(); ++y)
    {
        for (size_t x = 0; x < data[y].size(); ++x)
        {
            if (data[y][x])
            {
                setNodeColor(offX + x, offY + y, color);
            }
        }
    }
}

void Grid::setBlock(Block& block)
{
    modBlockBase(block.getX(), block.getY(), block.getTemplateData(), block.getColor());
    block.lock();
}

void Grid::removeBlock(Block& block)
{
    modBlockBase(block.getX(), block.getY(), block.getTemplateData(), blank);
    block.unlock();
}

void Grid::draw()   
{
    float blockSize = square.getSize();
    square.setPosition(square.getX(), 0.0f);
    for (size_t y = 0; y < grid.size(); ++y)
    {
        for (size_t x = 0; x < grid[y].size(); ++x)
        {
            const auto& node(grid[y][x]);
            square.setColor(node);
            square.draw();
            square.translate(blockSize, 0.0f);
        }
        square.translate(-blockSize * grid[y].size(), blockSize);
    }
}