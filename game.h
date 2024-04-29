#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "player.h"
#include "ball.h"

enum GameState {
	GAME_ACTIVE,
	GAME_WIN
};

class Game
{

public:
	Game(std::string player1Type, std::string player2Type, int limit);
	~Game();
	void MainLoop(GLFWwindow* window);
	int score[2];
	void State_change(GameState newState) { State = newState; }
	static void getKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool getKey(int keyI);
	GLuint gameVAO, gameVBO;
	GLfloat gameVertices[100];

	int limit = 5;
	void renderGame(GLFWwindow* window);
	void renderWin(GLFWwindow* window);
	void render(PlayerSide side, int score);


	void draw(PlayerSide side, int score);
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
	std::string updateWindow();
	std::string windowScore;


protected:
	Ball ball;
	Player* Player1;
	Player* Player2;

private:
	void reset(PlayerSide sideWon);
	GameState State = GameState::GAME_ACTIVE;
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool keys[5]; //{W, S, UP, DOWN}

};

