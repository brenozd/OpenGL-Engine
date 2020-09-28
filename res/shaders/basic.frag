#version 330 core

out vec4 color;
in vec4 v_Color;
uniform vec4 u_Color;

void main()
{
    color = (v_Color + u_Color);
};