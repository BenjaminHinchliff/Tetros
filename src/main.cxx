#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

namespace fs = std::filesystem;

constexpr int SCR_WIDTH = 640;
constexpr int SCR_HEIGHT = 480;

int main()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to init" << '\n';
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Window failed to create" << '\n';
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initilize GLAD" << '\n';
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	std::ifstream vertexFile("Rect.vert");
	std::string vertexString((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
	const char* vertexSource = vertexString.c_str();

	std::ifstream fragFile("Rect.frag");
	std::string fragString((std::istreambuf_iterator<char>(fragFile)), std::istreambuf_iterator<char>());
	const char* fragSource = fragString.c_str();

	Shader shader(vertexSource, fragSource);

	std::array<float, 8> vertices{
		-0.5f, -0.5f, // left bottom
		-0.5f,  0.5f, // left top
		 0.5f,  0.5f, // right top
		 0.5f, -0.5f, // right bottom
	};

	std::array<uint32_t, 6> indices{
		0, 2, 1,
		0, 3, 2,
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}