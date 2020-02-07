#ifndef BLOCK_H
#define BLOCK_H

#include <array>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "TexturedMesh.h"

class Block
{
public:
	Block();
	Block(float x, float y, float size, const glm::vec3& color, const glm::mat4& projection);

	void translate(float x, float y);
	void rescale(float factor);

	void draw() const;
private:
	static Shader shader;
	static int matrixLoc;
	static int colorLoc;
	static TexturedMesh model;
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	std::vector<float> vertices{
		 // positions	// tex coords
		 1.0f,  1.0f,	1.0f, 1.0f,	// right top  
		 1.0f,  0.0f,	1.0f, 0.0f,	// right bottom
		 0.0f,  0.0f,	0.0f, 0.0f,	// left bottom
		 0.0f,  1.0f,	0.0f, 1.0f,	// left top 
	};
	std::vector<GLuint> indices{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
};

#endif // !BLOCK_H
