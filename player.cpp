#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "player.h"

Player::Player(std::string PlayerType, PlayerSide playerSide, std::string name, glm::vec3 color)
	: playerSide(playerSide), name(name), color(color)
{
	isUser = PlayerType == "User";
	location = 0.0f;
	moveDirection = Direction::NONE;
	width_l = 0.9;
	width_r = 0.85;
	legnth = -0.1;
	for (int i = 0; i < 4; i++) {
		rectVertices[i * 3] = (i == 0 || i == 3) ? -width_l * (-1 * playerSide) : -width_r * (-1 * playerSide); // x-coordinate
		rectVertices[i * 3 + 1] = (i < 2) ? -legnth + location : legnth + location;          // y-coordinate
		rectVertices[i * 3 + 2] = 0.0f;                            // z-coordinate
	}


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
		if (location + 0.1f < 1.0f) {
			location += 0.01f;
		}
		break;
	case Direction::DOWN:
		if (location - 0.1f > -1.0f) { 
			location -= 0.01f;
		}
		break;
	}

	render();
}

void Player::render() {

	//1000 - 600 //  (i == 0 || i == 3) ? -0.1f : 0.1f;

	for (int i = 0; i < 4; i++) {
		rectVertices[i * 3] = (i == 0 || i == 3) ? -width_l * (-1 * playerSide) : -width_r * (-1 * playerSide); // x-coordinate
		rectVertices[i * 3 + 1] = (i < 2) ? -legnth + location : legnth + location;          // y-coordinate
		rectVertices[i * 3 + 2] = 0.0f;                            // z-coordinate
	}

	glBindBuffer(GL_ARRAY_BUFFER, playerVBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rectVertices), rectVertices); // Update buffer with new data

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(playerVAO);

	// Draw the player rectangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}




