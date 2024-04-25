#include "player.h"
#include <iostream>
#include <glm/glm.hpp>

Player::Player(std::string PlayerType, PlayerSide playerSide, std::string name, glm::vec3 color)
	: playerSide(playerSide), name(name), color(color)
{
	isUser = PlayerType == "User";
	location = 0.0f;
	moveDirection = Direction::NONE;
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
		location += 0.1f;
		break;
	case Direction::DOWN:
		location -= 0.1f;
		break;
	}
}



