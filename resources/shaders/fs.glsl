#version 450 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D sprite_texture;

void main()
{
    FragColor = texture(sprite_texture, TexCoords);
}