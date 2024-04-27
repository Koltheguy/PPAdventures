#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>

static const float PLAYER_DISTANCE = 0.9f;
static const float PLAYER_SPEED = 0.015f;

enum Direction {
	NONE,
	UP,
	DOWN,
};

enum PlayerSide {
	LEFT = -1,
	RIGHT = 1,
};

class Player
{
public:
	Player(std::string playerType, PlayerSide playerSide, std::string name, glm::vec3 color);

	bool isUser;
	GLuint playerVAO, playerVBO;

	PlayerSide playerSide;
	
	float width;
	float length;
	//rectVertices - has 4 vertices each with x,y,z coordinates
	GLfloat rectVertices[4 * 3];

	std::string name;
	glm::vec3 color;
	Direction moveDirection;
	float location;

	void handleKeyPress(bool isUp, bool isDown);
	virtual void update();
	void draw();
	void render();
};


