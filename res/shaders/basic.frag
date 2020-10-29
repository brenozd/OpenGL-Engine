#version 330 core

out vec4 color;

in vec4 v_Color;
in vec2 v_Text;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){
    color = texture(u_Texture, v_Text);
};