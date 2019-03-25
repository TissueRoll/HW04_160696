#version 330 core

layout(location = 0) in vec3 v_pos; // 0 is position
layout(location = 1) in vec4 v_color; // 1 is color
layout(location = 2) in vec2 tex_coords; // 2 is texture

out vec2 f_texCoords;

void main() {
	f_texCoords = tex_coords;
	gl_Position = v_pos;
}