#include "game.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "player.h"

bool Game::keys[4] = { 0, 0, 0 ,0 };

void Game::MainLoop(GLFWwindow* window) {
	// handle inputs
	if (Player1.isUser)
		Player1.handleKeyPress(keys[0], keys[1]);
	if (Player2.isUser)
		Player2.handleKeyPress(keys[2], keys[3]);
	Player1.update();
	Player2.update();
	ball.update(); // Note that the data from this function call is only used within the scope of this function and not actually used in the main render loop in main.cpp
	std::cout << Player1.location << " " <<
		Player2.location << " " <<
		ball.location[0] << "," << ball.location[1] <<
		std::endl;
}

Game::Game(Player P1, Player P2) : Player1(P1), Player2(P2) {
	Game::keys[0] = 0; //W
	Game::keys[1] = 0; //S
	Game::keys[2] = 0; //UP
	Game::keys[3] = 0; //DOWN
};

bool Game::getKey(int keyI) {
	return Game::keys[keyI];
}

void Game::getKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keyCallback(window, key, scancode, action, mods);
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// actions are GLFW_PRESS == 0, GLFW_RELEASE == 1
	if (action == GLFW_PRESS || action == GLFW_RELEASE)
		switch (key) {
		case GLFW_KEY_W:
			Game::keys[0] = action;
			break;
		case GLFW_KEY_S:
			Game::keys[1] = action;
			break;

		case GLFW_KEY_UP:
			Game::keys[2] = action;
			break;
		case GLFW_KEY_DOWN:
			Game::keys[3] = action;
			break;

		case GLFW_KEY_UNKNOWN:
		default:
			std::cout << "Unknown Key Pressed" << std::endl;
			break;
		}
}