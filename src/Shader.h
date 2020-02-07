#ifndef SHADER_H
#define SHADER_H

#include <fstream>

#include <glad/glad.h>

class Shader
{
public:
	Shader();
	Shader(const char* vertexSource, const char* fragSource);
	Shader(std::ifstream vertexFile, std::ifstream fragfile);
	~Shader();

	Shader& operator=(Shader&& right) noexcept;

	operator int() const;

	bool exists() const;

	int getID() const;
private:
	int buildProgram(const char* vertexSource, const char* fragmentSource) const;

	int shaderProgram = 0;
};

#endif // !SHADER_H
