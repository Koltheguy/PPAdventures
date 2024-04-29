#include "game.h"
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "playerFactory.h"
#include "player.h"
#include "simpleAi.h"

bool Game::keys[5] = { 0, 0, 0 ,0 ,0};

Game::Game(std::string player1Type, std::string player2Type, int Limit)
	: Player1(PlayerFactory::createPlayer(player1Type, PlayerSide::LEFT, "Player 1", glm::vec3(1.0f))), 
	Player2(PlayerFactory::createPlayer(player2Type, PlayerSide::RIGHT, "Player 2", glm::vec3(1.0f)))
{	
	limit = Limit;
	ball.setPlayer1(Player1);
	ball.setPlayer2(Player2);
	Player1->setBall(&ball);
	Player2->setBall(&ball);
	Player1->setOtherPlayer(Player2);
	Player2->setOtherPlayer(Player1);
	State_change(GAME_ACTIVE);
	score[0] = 0;
	score[1] = 0;

	keys[0] = 0; //W
	keys[1] = 0; //S
	keys[2] = 0; //UP
	keys[3] = 0; //DOWN
	keys[4] = 0; //Enter

	// Generate the playerVAO and playerVBO with only 1 object each for the ball
	glGenVertexArrays(1, &gameVAO);
	glGenBuffers(1, &gameVBO);

	// Make the playerVAO the current vertext array object by binding it
	glBindVertexArray(gameVAO);

	// Binding the playerVBO and telling the computer it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, gameVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gameVertices), gameVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
};

Game::~Game() {
	delete Player1;
	delete Player2;
}

void Game::MainLoop(GLFWwindow* window) {
	// handle inputs
	switch (State) {
	/*case GameState::GAME_MENU:
		renderMenu();
		break;*/
	case GameState::GAME_ACTIVE:
		renderGame(window);
		break;
	case GameState::GAME_WIN:
		renderWin(window);
		break;
	default:
		break;
	}
}
void Game::renderGame(GLFWwindow* window) {
	if (Player1->isUser)
		Player1->handleKeyPress(keys[0], keys[1]);
	if (Player2->isUser)
		Player2->handleKeyPress(keys[2], keys[3]);
	/*render(RIGHT, score[1]);
	render(LEFT, score[0]);*/
	Player1->update();
	Player2->update();
	ball.update();
	windowScore = updateWindow();
	glfwSetWindowTitle(window, windowScore.c_str());

	if (ball.location[0] < -1.01f) {
		reset(PlayerSide::RIGHT);
	}
	else if (ball.location[0] > 1.01f) {
		reset(PlayerSide::LEFT);
	}
	if (score[0] == limit || score[1] == limit) {
		State_change(GAME_WIN);

	}
}

void Game::renderWin(GLFWwindow* window) {
	if (score[0] == limit) {
		std::string winner = "Player 1 Won (Press enter to reset)";
		glfwSetWindowTitle(window, winner.c_str());
	}
	else if (score[1] == limit) {
		std::string winner = "Player 2 Won (Press enter to reset)";
		glfwSetWindowTitle(window, winner.c_str());
	}
	if (keys[4] == 1) {
		score[0] = 0;
		score[1] = 0;
		reset(PlayerSide::RIGHT);
		reset(PlayerSide::LEFT);
		State_change(GAME_ACTIVE);
	}
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
	//std::cout << Player1->location << " " <<
	//	Player2->location << " " <<
	//	ball.location[0] << "," << ball.location[1] <<
	//	std::endl;
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
		case GLFW_KEY_ENTER: // Check for Enter key
			keys[4] = action;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, 1);
			break;

		case GLFW_KEY_UNKNOWN:
		default:
			std::cerr << "Unknown Key Pressed" << std::endl;
			break;
		}
}

std::string Game::updateWindow() {
	std::string score1 = std::to_string(score[0]);
	std::string score2 = std::to_string(score[1]);
	std::string name = "PPAdventures SCORE: ";
	name += score1;
	name += " - ";
	name += score2;

	return name;
}