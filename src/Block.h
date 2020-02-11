#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <algorithm>

#include <glm/glm.hpp>

using templateData_t = std::vector<std::vector<bool>>;

struct BlockTemplate
{
    templateData_t templateData;
    glm::vec3 color;
};

class Block
{
public:
    Block();
    Block(int x, int y, const BlockTemplate& blockTemplate);

    void setX(int x);
    void setY(int y);
    void changeX(int x);
    void changeY(int y);

    void rotate();
    void unrotate();

    int getX() const;
    int getY() const;
    const templateData_t& getTemplateData() const;
    const glm::vec3& getColor() const;
    size_t getWidth() const;
    size_t getHeight() const;
    bool getLocked() const;

    int getBufX() const;
    int getBufY() const;

    void lock();
    void unlock();

private:
    void updateData();

    int x = 0;
    int y = 0;
    bool locked = false;
    int bufX = 0;
    int bufY = 0;
    templateData_t templateData = {};
    templateData_t templateBuf = {};
    glm::vec3 color = { 0.0f, 0.0f, 0.0f };
};

#endif // !BLOCK_H
