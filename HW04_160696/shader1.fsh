#version 330 core

in vec2 f_texCoords;

out vec4 fragColor;

uniform sampler2D tex0;

void main(){
	fragColor = texture(tex0, f_texCoords);
	//fragColor = f_color;
}
