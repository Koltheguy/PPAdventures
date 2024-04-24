#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ball.h"

Ball::Ball() {
	location[0] = 0.0f;
	location[1] = 0.0f;
	velocity[0] = 0.00010f;
	velocity[1] = -0.00020f;
}

void Ball::update() {
	location[0] += velocity[0];
	location[1] += velocity[1];

	//edge detection
	if (location[0] > 50 || location[0] < -50)
		velocity[0] = -velocity[0];
	if (location[1] > 50 || location[1] < -50)
		velocity[1] = -velocity[1];
}

GLuint Ball::render(GLFWwindow* window) {
	const char* vertexShaderSourceBall = "#version 330 core\n"  // Vertex for ball
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSourceBall = "#version 330 core\n" // fragment for ball
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n\0";

	// Create Vertex Shader object for the ball
	GLuint vertexShaderBall = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderBall, 1, &vertexShaderSourceBall, NULL);
	glCompileShader(vertexShaderBall);

	// Create Fragment Shader object for the ball
	GLuint fragmentShaderBall = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderBall, 1, &fragmentShaderSourceBall, NULL);
	glCompileShader(fragmentShaderBall);

	// Create the shader program object for the ball and get its reference
	GLuint shaderProgramBall = glCreateProgram();
	glAttachShader(shaderProgramBall, vertexShaderBall);
	glAttachShader(shaderProgramBall, fragmentShaderBall);

	// Link the shaders into the shader program
	glLinkProgram(shaderProgramBall);

	// We don't need the vertex and fragment shader objects so delete em
	glDeleteShader(vertexShaderBall);
	glDeleteShader(fragmentShaderBall);

	return shaderProgramBall;
}