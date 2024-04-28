#include "game.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "playerFactory.h"
#include "player.h"
#include "simpleAi.h"

bool Game::keys[4] = { 0, 0, 0 ,0 };

Game::Game(std::string player1Type, std::string player2Type)
	: Player1(PlayerFactory::createPlayer(player1Type, PlayerSide::LEFT, "Player 1", glm::vec3(1.0f))), 
	Player2(PlayerFactory::createPlayer(player2Type, PlayerSide::RIGHT, "Player 2", glm::vec3(1.0f)))
{
	ball.setPlayer1(Player1);
	ball.setPlayer2(Player2);
	Player1->setBall(&ball);
	Player2->setBall(&ball);

	score[0] = 0;
	score[1] = 0;

	keys[0] = 0; //W
	keys[1] = 0; //S
	keys[2] = 0; //UP
	keys[3] = 0; //DOWN
};

void Game::MainLoop() {
	// handle inputs
	if (Player1->isUser)
		Player1->handleKeyPress(keys[0], keys[1]);
	if (Player2->isUser)
		Player2->handleKeyPress(keys[2], keys[3]);

	Player1->update();
	Player2->update();
	ball.update();

	if (ball.location[0] < -1.01f) {
		reset(PlayerSide::RIGHT);
	} else if (ball.location[0] > 1.01f) {
		reset(PlayerSide::LEFT);
	}

	std::cout << Player1->location << " " <<
		Player2->location << " " <<
		ball.location[0] << "," << ball.location[1] <<
		std::endl;
}

void Game::reset(PlayerSide sideWon) {
	Player1->location = 0.0f;
	Player2->location = 0.0f;
	ball.location[0] = 0.0f;
	ball.location[1] = 0.0f;
	ball.velocity[0] = 0.0f;
	ball.velocity[1] = 0.0f;
	switch (sideWon) {
	case PlayerSide::RIGHT:
		score[1]++;
		ball.velocity[0] = -BALL_SPEED;
		break;
	case PlayerSide::LEFT:
		score[0]++;
		ball.velocity[0] = BALL_SPEED;
		break;
	}
}

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

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, 1);
			break;

		case GLFW_KEY_UNKNOWN:
		default:
			std::cout << "Unknown Key Pressed" << std::endl;
			break;
		}
}