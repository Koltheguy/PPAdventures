#pragma once
#include <glad/glad.h>

static const float BALL_SPEED = 0.015f;
static const float BALL_SPEED_DELTA = 0.0005f;

class Ball
{
public:
	Ball();
	GLfloat ballVertices[360 * 3];
	// Create reference containers for the array and buffers objects for the vertex
	GLuint ballVAO, ballVBO;
	const float radius = 0.025f;
	float location[2];
	float velocity[2];
	void update();
	void render();
};

