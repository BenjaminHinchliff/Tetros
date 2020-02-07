#include "TexturedMesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

TexturedMesh::TexturedMesh()
    : Mesh()
{
}

TexturedMesh::TexturedMesh(
    const std::vector<float>& inVerticies,
    const std::vector<GLuint>& inIndicies,
    const char* texturePath
)
    : Mesh(inVerticies, inIndicies, 4 * sizeof(float))
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int nrChannels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    GLenum channelsConst = nrChannels == 4 ? GL_RGBA : GL_RGB;
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, channelsConst, width, height, 0, channelsConst, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("Failed to load Texture");
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

TexturedMesh& TexturedMesh::operator=(TexturedMesh&& other) noexcept
{
    VAO = other.VAO;
    other.VAO = 0;
    VBO = other.VBO;
    other.VBO = 0;
    EBO = other.EBO;
    other.EBO = 0;
    texture = other.texture;
    other.texture = 0;
    vertices = other.vertices;
    indices = other.indices;
    return *this;
}

void TexturedMesh::draw() const
{
    glBindTexture(GL_TEXTURE_2D, texture);
    Mesh::draw();
    glBindTexture(GL_TEXTURE_2D, 0);
}