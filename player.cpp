#include "player.h"
#include <iostream>
#include <glm/glm.hpp>

Player::Player(bool isUser, PlayerSide playerSide, std::string name, glm::vec3 color)
	: isUser(isUser), playerSide(playerSide), name(name), color(color)
{
	location = 0.0f;
	direction = Direction::NONE;
}

void Player::handleKeyPress(bool isUp, bool isDown) {
	if (isUp && !isDown)
		direction = Direction::UP;
	else if (isDown && !isUp)
		direction = Direction::DOWN;
	else
		direction = Direction::NONE;
}

void Player::update() {
	switch (direction) {
	case Direction::UP:
		location += 0.1f;
		break;
	case Direction::DOWN:
		location -= 0.1f;
		break;
	}
}



