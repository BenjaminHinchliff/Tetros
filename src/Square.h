#ifndef SQUARE_H
#define SQUARE_H

#include <array>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "TexturedMesh.h"

class Square
{
public:
	Square();
	Square(float x, float y, float size, const glm::vec3& color, const glm::mat4& projection);

	void translate(float x, float y);
	void setPosition(float x, float y);
	void rescale(float factor);
	void setColor(const glm::vec3& color);

	void draw() const;

	float getSize() const;
	float getX() const;
	float getY() const;
private:
	void applyMatrix();

	static Shader shader;
	static int matrixLoc;
	static int colorLoc;
	static TexturedMesh model;
	float size = 1.0f;
	float x = 0;
	float y = 0;
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

#endif // !SQUARE_H
