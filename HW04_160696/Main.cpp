#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// is this working

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;
const float temp_scale = 0.5f;

struct Vertex {
	GLfloat x, y, z; // position
	GLubyte r, g, b, a; // color
	GLfloat u, v;
};

Vertex vertices[] = {
	//   x      y  z    r    g    b  a
	{-0.5f,  0.5f, 0, 255, 255, 255, 1},
	{-0.5f, -0.5f, 0, 255, 255, 255, 1},
	{ 0.5f,  0.5f, 0, 255, 255, 255, 1},
	{ 0.5f, -0.5f, 0, 255, 255, 255, 1}
};

GLfloat p1_rand_r, p1_rand_g, p1_rand_b, p1_rand_a, p2_rand_r, p2_rand_g, p2_rand_b, p2_rand_a, scaling;
bool space_pressed, k1_pressed, k2_pressed, k3_pressed, k4_pressed, kUP_pressed, traj;

int main() {
	// initializing values
	p1_rand_r = (float)(rand() % 256) / 255.f;
	p1_rand_g = (float)(rand() % 256) / 255.f;
	p1_rand_b = (float)(rand() % 256) / 255.f;
	p1_rand_a = (float)(rand() % 256) / 255.f;
	p2_rand_r = (float)(rand() % 256) / 255.f;
	p2_rand_g = (float)(rand() % 256) / 255.f;
	p2_rand_b = (float)(rand() % 256) / 255.f;
	p2_rand_a = (float)(rand() % 256) / 255.f;
	// p1_rand_r = p1_rand_b = p1_rand_g = p1_rand_a = 1.f;
	// p2_rand_r = p2_rand_b = p2_rand_g = p2_rand_a = 1.f;
	scaling = 1.f;
	space_pressed = k1_pressed = k2_pressed = k3_pressed = k4_pressed = kUP_pressed = traj = 0;
	srand(time(NULL));
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CS177", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// gl stuff
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string out;
	std::ifstream f;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	// vertex shader
	std::string vsh;
    f.open("shader1.vsh");
	if (f.is_open()) {
		while (std::getline(f, out)) {
			vsh.append(out + "\n");
		}
		f.close();
	}
	else {
		std::cout << "Unable to open vertex shader file.";
	}
	vertexShaderSource = vsh.c_str();
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// fragment shader
	std::string fsh;
	f.open("shader1.fsh");
	if (f.is_open()) {
		while (std::getline(f, out)) {
			fsh.append(out + "\n");
		}
		f.close();
	}
	else {
		std::cout << "Unable to open fragment shader file.";
	}
	fragmentShaderSource = fsh.c_str();
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// making a program
	int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*
	std::string vsh2;
	f.open("shader2.vsh");
	if (f.is_open()) {
		while (std::getline(f, out)) {
			vsh2.append(out + "\n");
		}
		f.close();
	}
	else {
		std::cout << "Unable to open vertex shader file.";
	}
	vertexShaderSource = vsh2.c_str(); // const char* vertexShaderSource = vsh2.c_str();
	int vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader2, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader2);

	std::string fsh2;
	f.open("shader2.fsh");
	if (f.is_open()) {
		while (std::getline(f, out)) {
			fsh2.append(out + "\n");
		}
		f.close();
	}
	else {
		std::cout << "Unable to open fragment shader file.";
	}
	fragmentShaderSource = fsh2.c_str(); // const char* fragmentShaderSource = fsh2.c_str();
	int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader2);

	GLuint program2 = glCreateProgram();
	glAttachShader(program2, vertexShader2);
	glAttachShader(program2, fragmentShader2);
	glLinkProgram(program2);

	glDeleteShader(vertexShader2);
	glDeleteShader(fragmentShader2);
	*/

	// linking vertex attributes
	GLuint tex0;
	glGenTextures(1, &tex0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, numChannels;
	auto data = stbi_load("pepethink.jpg", &width, &height, &numChannels, 0);
	if (data) { // check if data contains something
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// glGenerateMipmap generates mipmaps after loading a texture
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture." << std::endl;
	}
	stbi_image_free(data);
	glActiveTexture(GL_TEXTURE0);
	// glBindTexture now binds the texture to the currently active texture unit
	glBindTexture(GL_TEXTURE_2D, tex0);
	glUniform1i(glGetUniformLocation(program, "tex0"), 0);
	stbi_set_flip_vertically_on_load(true);


	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, r));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

	// get uniform locations
	// program 1
	auto scaleFactor = glGetUniformLocation(program, "scaleFactor");
	auto p1_red = glGetUniformLocation(program, "red");
	auto p1_green = glGetUniformLocation(program, "green");
	auto p1_blue = glGetUniformLocation(program, "blue");
	auto p1_alpha = glGetUniformLocation(program, "alpha");

	/*
	// program 2
	auto x_coord = glGetUniformLocation(program2, "x_coord");
	auto y_coord = glGetUniformLocation(program2, "y_coord");
	auto p2_red = glGetUniformLocation(program2, "red");
	auto p2_green = glGetUniformLocation(program2, "green");
	auto p2_blue = glGetUniformLocation(program2, "blue");
	auto p2_alpha = glGetUniformLocation(program2, "alpha");
	*/

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		glUniform1f(scaleFactor, scaling);
		glUniform1f(p1_red, p1_rand_r);
		glUniform1f(p1_green, p1_rand_g);
		glUniform1f(p1_blue, p1_rand_b);
		glUniform1f(p1_alpha, p1_rand_a);
		glBindVertexArray(vao);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		/*
		glUseProgram(program2);
		glUniform1f(p2_red, p2_rand_r);
		glUniform1f(p2_green, p2_rand_g);
		glUniform1f(p2_blue, p2_rand_b);
		glUniform1f(p2_alpha, p2_rand_a);
		glUniform1f(x_coord, (traj ? cos(0.5f*glfwGetTime())*temp_scale : sin(0.5f*glfwGetTime())*temp_scale));
		glUniform1f(y_coord, (traj ? sin(0.5f*glfwGetTime())*temp_scale : cos(0.5f*glfwGetTime())*temp_scale));
		//glBindVertexArray(vao);
		//glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(program); // clean-up

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!space_pressed) {
			space_pressed = 1;
			p2_rand_r = (float)(rand() % 256) / 255.f;
			p2_rand_g = (float)(rand() % 256) / 255.f;
			p2_rand_b = (float)(rand() % 256) / 255.f;
			p2_rand_a = (float)(rand() % 256) / 255.f;
		}
	}
	else {
		space_pressed = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		if (!k1_pressed) {
			k1_pressed = 1;
			p1_rand_r = (float)(rand() % 256) / 255.f;
		}
	}
	else {
		k1_pressed = 0;
	}
	
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		if (!k2_pressed) {
			k2_pressed = 1;
			p1_rand_g = (float)(rand() % 256) / 255.f;
		}
	}
	else {
		k2_pressed = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		if (!k3_pressed) {
			k3_pressed = 1;
			p1_rand_b = (float)(rand() % 256) / 255.f;
		}
	}
	else {
		k3_pressed = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		if (!k4_pressed) {
			k4_pressed = 1;
			p1_rand_a = (float)(rand() % 256) / 255.f;
		}
	}
	else {
		k4_pressed = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (!kUP_pressed) {
			kUP_pressed = 1;
			traj = !traj;
		}
	} 
	else {
		kUP_pressed = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		scaling = (scaling - 0.001f < 0.f ? 0.f : scaling - 0.01f);
	}
	
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		scaling += 0.01f; // (scaling + 0.001f > 1.f ? 1.f : scaling + 0.001f);
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}