#version 330 core

in vec4 f_color;

out vec4 fragColor;
uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;

void main(){
	fragColor = vec4(red, green, blue, alpha);
	//fragColor = f_color;
}
