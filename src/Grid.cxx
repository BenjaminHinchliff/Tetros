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

bool Grid::testCollisions(const Block& block)
{
    const templateData_t data(block.getTemplateData());
    for (size_t y = 0; y < block.getHeight(); ++y)
    {
        for (size_t x = 0; x < block.getWidth(); ++x)
        {
            constexpr float epsilon = std::numeric_limits<float>::epsilon();
            if (data[y][x] && glm::length2(grid[block.getBufY() + y][block.getBufX() + x] - blank) > epsilon * epsilon)
            {
                return true;
            }
        }
    }
    return false;
}

bool Grid::testInBounds(const Block& block)
{
    return block.getBufY() >= 0
        && block.getBufY() + block.getHeight() <= grid.size()
        && block.getBufX() >= 0
        && block.getBufX() + block.getWidth() <= grid[0].size();
}

void Grid::clearLines()
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    for (size_t y = 0; y < grid.size(); ++y)
    {
        bool cleared = true;
        for (const auto& vecItem : grid[y])
        {
            if (glm::length2(vecItem) < epsilon * epsilon)
            {
                cleared = false;
            }
        }
        if (cleared)
        {
            for (auto& item : grid[y])
            {
                item = glm::vec3(0.0f, 0.0f, 0.0f);
            }
            for (int sy = y - 1; sy >= 0; --sy)
            {
                grid[sy + 1] = grid[sy];
            }
        }
    }
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

void Grid::printGrid() const
{
    for (const auto& arr : grid)
    {
        for (const auto& color : arr)
        {
            std::cout << '(' << color.x << ' ' << color.y << ' ' << color.z << ") ";
        }
        std::cout << '\n';
    }
}