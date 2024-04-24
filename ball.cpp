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
	velocity[0] = 1.24356f;
	velocity[1] = -1.213456f;
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

void Ball::render() {
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

	// Here is the vertex coordinates so we can dictate the shape of the ball
	GLfloat ballVertices[360 * 3]; // this is what makes it a circle
	const float radius = 0.025f;
	for (int i = 0; i < 360; i++) {
		float radians = glm::radians(static_cast<float>(i));
		ballVertices[i * 3] = cos(radians) * radius;
		ballVertices[i * 3 + 1] = sin(radians) * radius * (1000.0f / 600.0f);
		ballVertices[i * 3 + 2] = 0.0f;
	}

	// Create reference containers for the array and buffers objects for the vertex
	GLuint ballVAO, ballVBO;

	// Generate the ballVAO and ballVBO with only 1 object each for the ball
	glGenVertexArrays(1, &ballVAO);
	glGenBuffers(1, &ballVBO);

	// Make the ballVAO the current vertext array object by binding it
	glBindVertexArray(ballVAO);

	// Binding the ballVBO and telling the computer it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ballVertices), ballVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Use the shader program
	glUseProgram(shaderProgramBall);

	// Bind the ballVAO
	glBindVertexArray(ballVAO);

	// Draw the ball
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);

	// Unbind the ballVAO
	glBindVertexArray(0);

	// Unuse the shader program
	glfwPollEvents();
}