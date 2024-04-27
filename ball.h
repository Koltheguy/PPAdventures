#pragma once
#include <glad/glad.h>
class Ball
{
public:
	Ball();
	GLfloat ballVertices[360 * 3];
	// Create reference containers for the array and buffers objects for the vertex
	GLuint ballVAO, ballVBO;
	const float radius = 0.025f;
	float location[2];
	void setPlayer1(Player* p) { player1 = p; }
	void setPlayer2(Player* p) { player2 = p; }

	float velocity[2];
	void update();
	void render();

private:
	Player* player1;
	Player* player2;
};
