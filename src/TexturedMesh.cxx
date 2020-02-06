#include "TexturedMesh.h"

TexturedMesh::TexturedMesh()
	: Mesh()
{
}

TexturedMesh::TexturedMesh(
	const std::vector<float>& inVerticies,
	const std::vector<GLuint>& inIndicies,
	const char* texturePath
)
	: Mesh(inVerticies, inIndicies)
{

}