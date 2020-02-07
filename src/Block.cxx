#include "Block.h"

#include <iostream>

Shader Block::shader;
int Block::matrixLoc = -1;
int Block::colorLoc = -1;
TexturedMesh Block::model;

Block::Block()
{
    if (!shader.exists())
    {
        shader = Shader(std::ifstream("ColorAndText.vert"), std::ifstream("ColorAndText.frag"));
        colorLoc = glGetUniformLocation(shader, "uColor");
        matrixLoc = glGetUniformLocation(shader, "uMatrix");
    }
    if (!model)
    {
        model = TexturedMesh(vertices, indices, "container.jpg");
    }
}

Block::Block(float x, float y, float size, const glm::vec3& color, const glm::mat4& projection)
    : Block()
{
    translate(x, y);
    rescale(size);
    this->projection = projection;
    applyMatrix();
    glUseProgram(shader);
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));
    glUseProgram(0);
}

void Block::translate(float x, float y)
{
    translation = glm::translate(translation, glm::vec3(x, y, 0.0f));
    applyMatrix();
}

void Block::rescale(float factor)
{
    scale = glm::scale(scale, glm::vec3(factor, factor, 1.0f));
    applyMatrix();
}

void Block::applyMatrix()
{
    glUseProgram(shader);
    glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, glm::value_ptr(projection * translation * scale));
    glUseProgram(0);
}

void Block::draw() const
{
    glUseProgram(shader);
    model.draw();
    glUseProgram(0);
}