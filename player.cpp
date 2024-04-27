#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "player.h"
#include "ball.h"

Player::Player(std::string playerType, PlayerSide playerSide, std::string name, glm::vec3 color)
	: playerSide(playerSide), name(name), color(color)
{
	isUser = playerType == "User";
	location = 0.0f;
	moveDirection = Direction::NONE;
	width = 0.05f;
	length = 0.1f;
	draw();

	// Generate the playerVAO and playerVBO with only 1 object each for the ball
	glGenVertexArrays(1, &playerVAO);
	glGenBuffers(1, &playerVBO);

	// Make the playerVAO the current vertext array object by binding it
	glBindVertexArray(playerVAO);

	// Binding the playerVBO and telling the computer it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, playerVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Player::handleKeyPress(bool isUp, bool isDown) {
	if (isUp && !isDown)
		moveDirection = Direction::UP;
	else if (isDown && !isUp)
		moveDirection = Direction::DOWN;
	else
		moveDirection = Direction::NONE;
}

void Player::update() {
	switch (moveDirection) {
	case Direction::UP:
		if (location + PLAYER_SPEED < 1.0f) {
			location += PLAYER_SPEED;
			if (location + length > 1.0f)
				location = 1.0f - length;
		}
		break;
	case Direction::DOWN:
		if (location - PLAYER_SPEED > -1.0f) {
			location -= PLAYER_SPEED;
			if (location - length < -1.0f)
				location = -1.0f + length;
		}
		break;
	}

	render();
}

void Player::render() {
	draw();

	glBindBuffer(GL_ARRAY_BUFFER, playerVBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rectVertices), rectVertices); // Update buffer with new data

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(playerVAO);

	// Draw the player rectangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Player::draw() {
	for (int i = 0; i <= 3; i++) {
		rectVertices[i * 3] = (i == 0 || i == 3) // x-coordinate
			? playerSide * (PLAYER_DISTANCE + width)	// back
			: playerSide * PLAYER_DISTANCE;				// front

		rectVertices[i * 3 + 1] = (i < 2) // y-coordinate
			? -length + location //bottom
			: length + location; //top

		rectVertices[i * 3 + 2] = 0.0f; // z-coordinate
	}

}




