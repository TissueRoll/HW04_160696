#version 330 core

layout(location = 0) in vec3 v_pos; // 0 is position
layout(location = 1) in vec4 v_color; // 1 is color
layout(location = 2) in vec2 tex_coords; // 2 is texture

out vec2 f_texCoords;

uniform float new_u;
uniform float new_v;

void main() {
	f_texCoords = vec2(((tex_coords.x - 0.5f)*new_u) + 0.5f, ((tex_coords.y - 0.5f)*new_v) + 0.5f);
	gl_Position = vec4(v_pos, 1.f);
}