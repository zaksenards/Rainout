#version 330 core

uniform vec4 vColor = vec4(0.5, 0.3, 0.7, 1.0);
uniform bool useTexture = false;
in vec2 TextCord;
out vec4 fColor;

uniform sampler2D s_texture;

void main()
{
    if(useTexture)
        fColor = texture(s_texture, TextCord);
    else
        fColor = vColor;
}
