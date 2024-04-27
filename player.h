#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
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
	
	//float width = 25.0f;
	//float height = 12.5f;
	//rectVertices - has 4 vertices each with x,y,z coordinates
	GLfloat rectVertices[4 * 3];

	std::string name;
	glm::vec3 color;
	Direction moveDirection;
	float location;

	void handleKeyPress(bool isUp, bool isDown);
	void render();
	virtual void update();
};


