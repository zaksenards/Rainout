#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 textCord;

uniform mat4 transform;
out vec2 TextCord;

void main()
{
    gl_Position = transform * vec4(vPos, 1.0);
    TextCord = textCord;
}
