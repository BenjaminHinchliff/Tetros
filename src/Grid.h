#ifndef GRID_H
#define GRID_H

#include <vector>

#include <glm/glm.hpp>

#include "Square.h"
#include "Block.h"

class Grid
{
public:
	Grid();
	Grid(int width, int height, float blockSize, glm::mat4 projection = glm::mat4(1.0f), float xOff = 0);

	void setNodeColor(int x, int y, const glm::vec3& color);

	void setBlock(Block& block);
	void removeBlock(Block& block);

	void draw();
private:
	void modBlockBase(int offX, int offY, const templateData_t& data, const glm::vec3& color);

	Square square;
	std::vector<std::vector<glm::vec3>> grid = {};

	const glm::vec3 blank{ 0.0f, 0.0f, 0.0f };
};

#endif // !GRID_H
