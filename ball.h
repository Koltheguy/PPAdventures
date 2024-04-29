#pragma once
#include <glad/glad.h>
#include "GameObject.h"

static const float BALL_SPEED = 0.015f;
static const float BALL_SPEED_MAX = 0.1f;
static const float BALL_SPEED_DELTA = 0.001f;
static const float BALL_MAX_BOUNCE = 1.309f; // 75 deg

class Player; // Forward Declaration

class Ball : public GameObject 
{
public:
	Ball();
	~Ball();
	GLfloat ballVertices[360 * 3];
	// Create reference containers for the array and buffers objects for the vertex
	GLuint ballVAO, ballVBO;
	const float radius = 0.025f;
	float location[2];
	void setPlayer1(Player* p) { Player1 = p; }
	void setPlayer2(Player* p) { Player2 = p; }

	float velocity[2];
	void calcVelocity(Player* player);

	void update();
	void draw() override;
	void render() override;

private:
	Player* Player1;
	Player* Player2;
};
