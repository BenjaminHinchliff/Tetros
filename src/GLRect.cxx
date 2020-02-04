#include "GLRect.h"

#include <iostream>


Shader GLRect::shader;
int GLRect::matLoc = -1;
int GLRect::colorLoc = -1;

GLRect::GLRect()
{
}

GLRect::GLRect(float x, float y, float width, float height, const glm::vec3& color, const glm::mat4& projection)
	: x(x), y(y), width(width), height(height), projection(projection)
{
	if (!shader)
	{
		std::ifstream vertexFile("GLRect.vert");
		std::string vertexString((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
		const char* vertexSource = vertexString.c_str();

		std::ifstream fragmentFile("GLRect.frag");
		std::string fragmentString((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
		const char* fragmentSource = fragmentString.c_str();

		shader = Shader(vertexSource, fragmentSource);
		matLoc = glGetUniformLocation(shader, "matrix");
		colorLoc = glGetUniformLocation(shader, "color");
	}

	std::array<float, 8> vertices{
		0.0f, 0.0f, // top left
		1.0f, 0.0f, // top right
		1.0f, 1.0f, // bottom right
		0.0f, 1.0f, // bottom left
	};

	std::array<uint32_t, 6> indices{
		3, 1, 0,
		3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	model = glm::translate(model, glm::vec3(x, y, 0));
	model = glm::scale(model, glm::vec3(width, height, 1));

	glUseProgram(shader);
	glUniform3fv(colorLoc, 1, glm::value_ptr(color));
	glUseProgram(0);
}

void GLRect::draw() const
{
	glUseProgram(shader);
	glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(projection * model));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
