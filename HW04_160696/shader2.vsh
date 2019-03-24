#version 330 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec4 v_color;

uniform float x_coord;
uniform float y_coord;

out vec4 f_color;

void main() {
	f_color = v_color;
	gl_Position = vec4(v_pos.x + x_coord, v_pos.y + y_coord, v_pos.z, 1.f);
	//gl_Position = vec4(v_pos.xyz*scale, 1.f);
}