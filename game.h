#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "player.h"
#include "ball.h"

static const float SCORE_DISTANCE = 0.6f;

class Game
{

public:
	Game(std::string player1Type, std::string player2Type);
	void MainLoop();
	int score[2];

	static void getKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool getKey(int keyI);
	GLuint gameVAO, gameVBO;
	GLfloat gameVertices[7 * 3]; // seven vertices to draw the score each with x, y and z coords
	void render(PlayerSide sideWon, int score);
	void draw(PlayerSide sideWon, int score);
	void zeroVertices(float xspacing, float yspacing);
	void oneVertices(float xspacing, float yspacing);
	void twoVertices(float xspacing, float yspacing);
	void threeVertices(float xspacing, float yspacing);
	void fourVertices(float xspacing, float yspacing);
	void fiveVertices(float xspacing, float yspacing);
	void sixVertices(float xspacing, float yspacing);
	void sevenVertices(float xspacing, float yspacing);
	void eightVertices(float xspacing, float yspacing);
	void nineVertices(float xspacing, float yspacing);

protected:
	Ball ball;
	Player Player1;
	Player Player2;

private:
	void reset(PlayerSide sideWon);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool keys[4]; //{W, S, UP, DOWN}

};

