#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "GameObject.h"

static const float PLAYER_DISTANCE = 0.95f;
static const float PLAYER_SPEED = 0.01f;

class Ball; // Forward Declaration

enum Direction {
	NONE = 0,
	UP = 1,
	DOWN = -1,
};

enum PlayerSide {
	LEFT = -1,
	RIGHT = 1,
};

class Player : GameObject
{
public:
	Player(std::string playerType, PlayerSide playerSide, std::string name, glm::vec3 color);
	~Player();
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
	void draw() override;
	void render() override;

	void setBall(Ball* b) { ball = b; }
	void setOtherPlayer(Player* p) { OtherPlayer = p; }


protected:
	Ball* ball;
	Player* OtherPlayer;

};


