#version 330 core

layout(location = 0) in vec3 v_pos; // 0 is position
layout(location = 1) in vec4 v_color; // 1 is color

out vec4 f_color;

uniform float scaleFactor;

void main() {
	f_color = v_color;
	//gl_Position = vec4(v_pos, 1.f);
	gl_Position = vec4(v_pos.xyz * scaleFactor, 1.f);
}