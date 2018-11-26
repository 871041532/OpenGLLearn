#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform float mixValue;

void main()
{
    FragColor = texture(texture1, vec2(TexCoord.x, TexCoord.y)) * vec4(ourColor, mixValue);
}