#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<float>& verticie, const std::vector<GLuint>& indices = {});
	~Mesh();

	Mesh& operator= (Mesh&& other) noexcept;

	void draw() const noexcept;

	const std::vector<float>& getVertices() const noexcept;
	const std::vector<GLuint>& getIndices() const noexcept;
protected:
	std::vector<float> vertices = {};
	std::vector<GLuint> indices = {};
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
};

#endif // !MESH_H
