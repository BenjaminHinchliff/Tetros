#include "Shader.h"

Shader::Shader()
{
}

Shader::Shader(const char* vertexSource, const char* fragSource)
	: shaderProgram(glCreateProgram())
{
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, nullptr);
	glCompileShader(fragShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

Shader& Shader::operator=(Shader&& right) noexcept
{
	shaderProgram = right.shaderProgram;
	right.shaderProgram = 0;
	return *this;
}

int Shader::getID() const
{
	return shaderProgram;
}

Shader::operator int() const
{
	return shaderProgram;
}