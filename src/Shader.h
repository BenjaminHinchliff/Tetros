#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

class Shader
{
public:
	Shader();
	Shader(const char* vertexSource, const char* fragSource);
	~Shader();

	int getID() const;

	operator int() const;
private:
	int shaderProgram = 0;
};

#endif // !SHADER_H
