#include "Square.h"

#include <iostream>

Shader Square::shader;
int Square::matrixLoc = -1;
int Square::colorLoc = -1;
TexturedMesh Square::model;

Square::Square()
{
}

Square::Square(float x, float y, float size, const glm::vec3& color, const glm::mat4& projection)
    : projection(projection)
{
    if (!shader.exists())
    {
        shader = Shader(std::ifstream("ColorAndText.vert"), std::ifstream("ColorAndText.frag"));
        colorLoc = glGetUniformLocation(shader, "uColor");
        matrixLoc = glGetUniformLocation(shader, "uMatrix");
    }
    if (!model)
    {
        model = TexturedMesh(vertices, indices, "block.png");
    }

    translate(x, y);
    rescale(size);
    glUseProgram(shader);
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));
    glUseProgram(0);
}

void Square::translate(float x, float y)
{
    this->x += x;
    this->y += y;
    translation = glm::translate(translation, glm::vec3(x, y, 0.0f));
    applyMatrix();
}

void Square::setPosition(float x, float y)
{
    translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    applyMatrix();
}

void Square::rescale(float factor)
{
    size *= factor;
    scale = glm::scale(scale, glm::vec3(factor, factor, 1.0f));
    applyMatrix();
}

void Square::setColor(const glm::vec3& color)
{
    glUseProgram(shader);
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));
    glUseProgram(0);
}

void Square::applyMatrix()
{
    glUseProgram(shader);
    glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, glm::value_ptr(projection * translation * scale));
    glUseProgram(0);
}

void Square::draw() const
{
    glUseProgram(shader);
    model.draw();
    glUseProgram(0);
}

float Square::getSize() const
{
    return size;
}

float Square::getX() const
{
    return x;
}

float Square::getY() const
{
    return y;
}