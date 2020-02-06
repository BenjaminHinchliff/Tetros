#include "Mesh.h"

#include <iostream>

Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<GLuint>& indices, size_t stride)
	: vertices(vertices), indices(indices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	if (indices.size() > 0)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

Mesh& Mesh::operator= (Mesh&& other) noexcept
{
	VAO = other.VAO;
	other.VAO = 0;
	VBO = other.VBO;
	other.VBO = 0;
	EBO = other.EBO;
	other.EBO = 0;
	vertices = other.vertices;
	indices = other.indices;
	return *this;
}

void Mesh::draw() const
{
	// std::cout << "base" << '\n';
	glBindVertexArray(VAO);
	if (EBO)
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 2);
	glBindVertexArray(0);
}

const std::vector<float>& Mesh::getVertices() const noexcept
{
	return vertices;
}

const std::vector<GLuint>& Mesh::getIndices() const noexcept
{
	return indices;
}