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
	velocity[0] = -BALL_SPEED;
	velocity[1] = 0.0f;

	// Here is the vertex coordinates so we can dictate the shape of the ball
	draw();

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

Ball::~Ball() {
	glDeleteVertexArrays(1, &ballVAO);
	glDeleteBuffers(1, &ballVBO);
}

void Ball::update() {
	location[0] += velocity[0];
	location[1] += velocity[1];
	//edge detection
	if (location[1] + radius > 1.0f || location[1] - radius < -1.0f)
		velocity[1] = -velocity[1];

	if ((location[0] - radius < -PLAYER_DISTANCE && location[0] > -PLAYER_DISTANCE - Player1->width) // x-pos
		&& (location[1] - radius < Player1->location + Player1->length && location[1] + radius > Player1->location - Player1->length) // y-pos
	) {
		calcVelocity(Player1);
		location[0] = -PLAYER_DISTANCE + radius;
	} else if ((location[0] + radius > PLAYER_DISTANCE && location[0] < PLAYER_DISTANCE + Player2->width) // x-pos
		&& (location[1] - radius < Player2->location + Player2->length && location[1] + radius > Player2->location - Player2->length) // y-pos
	) {
		calcVelocity(Player2);
		location[0] = PLAYER_DISTANCE - radius;
	}

	render();
}

void Ball::calcVelocity(Player* player) {

	float speed = sqrt(velocity[0] * velocity[0] + velocity[1] * velocity[1]) + BALL_SPEED_DELTA;

	float yDelta = location[1] - player->location;
	float bounceAngle = (yDelta / player->length) * BALL_MAX_BOUNCE;

	// convert to coords
	velocity[0] = -velocity[0] + BALL_SPEED_DELTA;
	velocity[1] = speed * sin(bounceAngle);

	if (velocity[0] > BALL_SPEED_MAX)
		velocity[0] = BALL_SPEED_MAX;
	else if (velocity[0] < -BALL_SPEED_MAX)
		velocity[0] = -BALL_SPEED_MAX;

	if (velocity[1] > BALL_SPEED_MAX)
		velocity[1] = BALL_SPEED_MAX;
	else if (velocity[1] < -BALL_SPEED_MAX)
		velocity[1] = -BALL_SPEED_MAX;
}

void Ball::render() {
	GameObject::render();
	// This will update the new vertices of the ball to match the changing location
	draw();

	glBindBuffer(GL_ARRAY_BUFFER, ballVBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ballVertices), ballVertices); // Update buffer with new data

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(ballVAO);

	// Draw the ball using the GL_TRIANGLE_FAN primitive
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
}

void Ball::draw() {
	for (int i = 0; i < 360; i++) {
		float radians = glm::radians(static_cast<float>(i));
		ballVertices[i * 3] = cos(radians) * radius + location[0];
		ballVertices[i * 3 + 1] = sin(radians) * radius * (1000.0f / 600.0f) + location[1];
		ballVertices[i * 3 + 2] = 0.0f;
	}
}


