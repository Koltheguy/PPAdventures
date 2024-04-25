#pragma once
#include <iostream>
#include <glm/glm.hpp>

enum Direction {
	NONE,
	UP,
	DOWN,
};

enum PlayerSide {
	LEFT,
	RIGHT,
};

class Player
{
public:
	Player(std::string playerType, PlayerSide playerSide, std::string name, glm::vec3 color);

	bool isUser;
	PlayerSide playerSide;
	std::string name;
	glm::vec3 color;
	Direction moveDirection;
	float location;

	void handleKeyPress(bool isUp, bool isDown);
	virtual void update();
};


