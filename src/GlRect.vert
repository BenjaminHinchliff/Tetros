#version 430 core
layout (location = 0) in vec2 aPos;

uniform mat4 matrix;
uniform vec3 color;

out vec3 fColor;

void main()
{
    gl_Position = matrix * vec4(aPos, 0, 1.0);
    fColor = color;
}