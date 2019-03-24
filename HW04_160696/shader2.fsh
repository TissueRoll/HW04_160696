#version 330 core

in vec4 f_color;

out vec4 pixelColor;

uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;

void main(){
	pixelColor = vec4(red, green, blue, alpha);
	//pixelColor = f_color;
}