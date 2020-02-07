#version 430 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec3 uColor;
uniform mat4 uMatrix;

out vec2 TexCoord;
out vec3 Color;

void main()
{
    gl_Position = uMatrix * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
    Color = uColor;
}