#ifndef TEXTURED_MESH_H
#define TEXTURED_MESH_H

#include "Mesh.h"

class TexturedMesh : protected Mesh
{
public:
	TexturedMesh();
	TexturedMesh(
		const std::vector<float>& verticies,
		const std::vector<GLuint>& indicies,
		const char* texturePath
	);
};

#endif // !TEXTURED_MESH_H
