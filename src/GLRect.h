#ifndef GL_RECT_H
#define GL_RECT_H

#include <array>
#include <fstream>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Debug.h"

class GLRect
{
public:
	GLRect();
	GLRect(float x, float y, float width, float height, const glm::vec3& color = glm::vec3(1.0, 1.0, 1.0), const glm::mat4& projection = glm::mat4(1.0f));

	void draw() const;
private:
	static Shader shader;
	static int matLoc;
	static int colorLoc;
	uint32_t VAO = 0;
	uint32_t VBO = 0;
	uint32_t EBO = 0;
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
};

#endif // !GL_RECT_H
