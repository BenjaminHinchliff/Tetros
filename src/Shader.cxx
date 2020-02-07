#include "Shader.h"

Shader::Shader()
{
}

Shader::Shader(const char* vertexSource, const char* fragmentSource)
	: shaderProgram(buildProgram(vertexSource, fragmentSource))
{
}

Shader::Shader(std::ifstream vertexFile, std::ifstream fragmentFile)
{
	std::string vertexString((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
	const char* vertexSource = vertexString.c_str();

	std::string fragmentString((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
	const char* fragmentSource = fragmentString.c_str();

	shaderProgram = buildProgram(vertexSource, fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

bool Shader::exists() const
{
	return static_cast<bool>(glIsProgram(shaderProgram));
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

int Shader::buildProgram(const char* vertexSource, const char* fragmentSource) const
{
	int shaderProgram = glCreateProgram();

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	return shaderProgram;
}