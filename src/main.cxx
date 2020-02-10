#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG
#include "Debug.h"
#endif // _DEBUG
#include "Shader.h"
#include "Mesh.h"
#include "TexturedMesh.h"
#include "Square.h"
#include "Grid.h"
#include "Block.h"
#include "BlockTemplates.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

constexpr int SCR_WIDTH = 640;
constexpr int SCR_HEIGHT = 480;
constexpr int GRID_WIDTH = 5;
constexpr int GRID_HEIGHT = 10;
constexpr int NODE_SIZE = static_cast<int>(SCR_HEIGHT / static_cast<float>(GRID_HEIGHT));
constexpr int X_OFFSET = static_cast<int>(SCR_WIDTH / 2.0 - NODE_SIZE * GRID_WIDTH / 2.0);

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
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // _DEBUG
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

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

#ifdef _DEBUG
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        // initialize debug output
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif // DEBUG

    glm::mat4 proj(glm::ortho<float>(0.0f, SCR_WIDTH, SCR_HEIGHT, 0.0f));

    Grid grid(GRID_WIDTH, GRID_HEIGHT, NODE_SIZE, proj, X_OFFSET);

    Block currentBlock(1, 0, blocks::L);

    glfwSetKeyCallback(window, keyCallback);

    constexpr double dropDelay = 1.0;

    double lastTime = glfwGetTime();
    double nextDrop = lastTime + dropDelay;
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (currentTime >= nextDrop)
        {
            currentBlock.changeY(1);
            nextDrop = currentTime + dropDelay;
        }
        grid.removeBlock(currentBlock);
        grid.setBlock(currentBlock);

        // std::cout << currentBlock.getLocked() << '\n';

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        grid.draw();

        glfwSetWindowUserPointer(window, &currentBlock);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Block& currentBlock = *static_cast<Block*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_RIGHT:
            currentBlock.changeX(1);
            break;
        case GLFW_KEY_LEFT:
            currentBlock.changeX(-1);
            break;
        default:
            break;
        }
    }
}