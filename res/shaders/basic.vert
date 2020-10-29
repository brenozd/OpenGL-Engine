#version 330 core

layout(location = 0) in vec3 m_position;
layout(location = 1) in vec4 m_color;
layout(location = 2) in vec2 m_text;

out vec4 v_Color;
out vec2 v_Text;

void main(){
    gl_Position = vec4(m_position,1.0);
    v_Color = m_color;
    v_Text = m_text;
};