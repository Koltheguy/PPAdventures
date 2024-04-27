#include "game.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "player.h"

bool Game::keys[4] = { 0, 0, 0 ,0 };

void Game::MainLoop() {
	// handle inputs
	if (Player1.isUser)
		Player1.handleKeyPress(keys[0], keys[1]);
	if (Player2.isUser)
		Player2.handleKeyPress(keys[2], keys[3]);
	Player1.update();
	Player2.update();
	ball.setPlayer1(&Player1);
	ball.setPlayer2(&Player2);
	ball.update();
	std::cout << Player1.location << " " <<
		Player2.location << " " <<
		ball.location[0] << "," << ball.location[1] <<
		std::endl;
}

Game::Game(std::string player1Type, std::string player2Type)
	: Player1(player1Type, PlayerSide::LEFT, "Player 1", glm::vec3(1.0f)), Player2(player2Type, PlayerSide::RIGHT, "Player 2", glm::vec3(1.0f))
{
	keys[0] = 0; //W
	keys[1] = 0; //S
	keys[2] = 0; //UP
	keys[3] = 0; //DOWN
};

bool Game::getKey(int keyI) {
	return keys[keyI];
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
			keys[0] = action;
			break;
		case GLFW_KEY_S:
			keys[1] = action;
			break;

		case GLFW_KEY_UP:
			keys[2] = action;
			break;
		case GLFW_KEY_DOWN:
			keys[3] = action;
			break;

		case GLFW_KEY_UNKNOWN:
		default:
			std::cout << "Unknown Key Pressed" << std::endl;
			break;
		}
}