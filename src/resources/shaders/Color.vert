#version 430 core
layout (location = 0) in vec4 aPos;

uniform vec3 color;

out vec3 aColor;

void main()
{
    gl_Position = aPos;
    aColor = color;
}