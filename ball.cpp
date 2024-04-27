#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "player.h"

#include "ball.h"

Ball::Ball() {
	location[0] = 0.0f;
	location[1] = 0.0f;
	velocity[0] = BALL_SPEED;
	velocity[1] = 0.0f;

	// Here is the vertex coordinates so we can dictate the shape of the ball
	for (int i = 0; i < 360; i++) {
		float radians = glm::radians(static_cast<float>(i));
		ballVertices[i * 3] = cos(radians) * radius;
		ballVertices[i * 3 + 1] = sin(radians) * radius * (1000.0f / 600.0f);
		ballVertices[i * 3 + 2] = 0.0f;
	}

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
}

void Ball::update() {
	location[0] += velocity[0];
	location[1] += velocity[1];
	GLfloat* rectVertices1 = player1->getRectVertices();
	GLfloat* rectVertices2 = player2->getRectVertices();
	//edge detection
	if (location[1] > 1 || location[1] < -1)
		velocity[1] = -velocity[1];

	//pong dection
	if ( (location[0] < rectVertices1[3] && location[1] < rectVertices1[1] && location[1] > rectVertices1[10]) ||
		(location[0] > rectVertices2[3] && location[1] < rectVertices2[1] && location[1] > rectVertices2[10])) {
		velocity[0] = -velocity[0];
	}
	
	//std::cout << rectVertices2[3] << "\n";

	render();
}

void Ball::render() {
	// This will update the new vertices of the ball to match the changing location
	for (int i = 0; i < 360; i++) {
		float radians = glm::radians(static_cast<float>(i));
		ballVertices[i * 3] = cos(radians) * radius + location[0];
		ballVertices[i * 3 + 1] = sin(radians) * radius * (1000.0f / 600.0f) + location[1];
		ballVertices[i * 3 + 2] = 0.0f;
	}

	glBindBuffer(GL_ARRAY_BUFFER, ballVBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ballVertices), ballVertices); // Update buffer with new data

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(ballVAO);

	// Draw the ball using the GL_TRIANGLE_FAN primitive
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
}


