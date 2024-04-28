#pragma once
#include <glad/glad.h>

static const float BALL_SPEED = 0.015f;
static const float BALL_SPEED_DELTA = 0.0005f;
static const float BALL_MAX_BOUNCE = 0.785398f; // 45 deg

class Player; // Forward Declaration

class Ball
{
public:
	Ball();
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
	void render();
	void draw();

private:
	Player* Player1;
	Player* Player2;
};
