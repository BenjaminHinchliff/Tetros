#version 430 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Color;

uniform sampler2D myTexture;

void main()
{
    FragColor = vec4(Color, 1.0) * texture(myTexture, TexCoord);
}