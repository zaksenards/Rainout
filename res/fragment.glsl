#version 330 core

uniform vec4 vColor = vec4(0.5, 0.3, 0.7, 1.0);
out vec4 fColor;

void main()
{
    fColor = vColor; 
}
