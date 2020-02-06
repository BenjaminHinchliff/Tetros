#ifndef TEXTURED_MESH_H
#define TEXTURED_MESH_H

#include "Mesh.h"

class TexturedMesh : public Mesh
{
public:
	TexturedMesh();
	TexturedMesh(
		const std::vector<float>& verticies,
		const std::vector<GLuint>& indicies,
		const char* texturePath
	);

	TexturedMesh& operator=(TexturedMesh&& other) noexcept;

	virtual void draw() const;
protected:
	GLuint texture = 0;
};

#endif // !TEXTURED_MESH_H
