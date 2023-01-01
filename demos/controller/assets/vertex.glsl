#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 textCord;

uniform vec2 spriteIndex;
uniform vec2 spriteScale;
uniform mat4 model;
out vec2 TextCord;

void main()
{
    gl_Position = model * vec4(vPos, 1.0);
    TextCord = textCord * spriteScale + spriteIndex;
}
