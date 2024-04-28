#include "game.h"
#include <iostream>
#include <string>
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
	Player1->setOtherPlayer(Player2);
	Player2->setOtherPlayer(Player1);

	score[0] = 0;
	score[1] = 0;

	keys[0] = 0; //W
	keys[1] = 0; //S
	keys[2] = 0; //UP
	keys[3] = 0; //DOWN

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
	if (Player1->isUser)
		Player1->handleKeyPress(keys[0], keys[1]);
	if (Player2->isUser)
		Player2->handleKeyPress(keys[2], keys[3]);
	render(RIGHT, score[1]);
	render(LEFT, score[0]);
	Player1->update();
	Player2->update();
	ball.update();
	windowScore = updateWindow();
	glfwSetWindowTitle(window, windowScore.c_str());

	if (ball.location[0] < -1.01f) {
		reset(PlayerSide::RIGHT);
	} else if (ball.location[0] > 1.01f) {
		reset(PlayerSide::LEFT);
	}

	//std::cout << Player1->location << " " <<
	//	Player2->location << " " <<
	//	ball.location[0] << "," << ball.location[1] <<
	//	std::endl;
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

std::string Game::updateWindow() {
	std::string score1 = std::to_string(score[0]);
	std::string score2 = std::to_string(score[1]);
	std::string name = "PPAdventures SCORE: ";
	name += score1;
	name += " - ";
	name += score2;

	return name;
}

void Game::render(PlayerSide sideWon, int score) {
	draw(sideWon, score);

	/*std::cout << "Game Vertices[0] = " << gameVertices[0] << std::endl;*/


	glBindBuffer(GL_ARRAY_BUFFER, gameVBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(gameVertices), gameVertices); // Update buffer with new data

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(gameVAO);

	// Draw the player score
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 7);

}

void Game::draw(PlayerSide side, int score) {
	float xspacing, yspacing;
	switch (side) {
	case LEFT:
		xspacing = -4.0f;
		yspacing = 4.0f;
		if (score == 0) {
			zeroVertices(xspacing, yspacing);
		}
		else if (score == 1) {
			oneVertices(xspacing, yspacing);
		}
		else if (score == 2) {
			twoVertices(xspacing, yspacing);
		}
		else if (score == 3) {
			threeVertices(xspacing, yspacing);
		}
		else if (score == 4) {
			fourVertices(xspacing, yspacing);
		}
		else if (score == 5) {
			fiveVertices(xspacing, yspacing);
		}
		else if (score == 6) {
			sixVertices(xspacing, yspacing);
		}
		else if (score == 7) {
			sevenVertices(xspacing, yspacing);
		}
		else if (score == 8) {
			eightVertices(xspacing, yspacing);
		}
		else if (score == 9) {
			nineVertices(xspacing, yspacing);
		}
		break;
	case RIGHT:
		xspacing = 4.0f;
		yspacing = 4.0f;
		if (score == 0) {
			zeroVertices(xspacing, yspacing);
		}
		else if (score == 1) {
			oneVertices(xspacing, yspacing);
		}
		else if (score == 2) {
			twoVertices(xspacing, yspacing);
		}
		else if (score == 3) {
			threeVertices(xspacing, yspacing);
		}
		else if (score == 4) {
			fourVertices(xspacing, yspacing);
		}
		else if (score == 5) {
			fiveVertices(xspacing, yspacing);
		}
		else if (score == 6) {
			sixVertices(xspacing, yspacing);
		}
		else if (score == 7) {
			sevenVertices(xspacing, yspacing);
		}
		else if (score == 8) {
			eightVertices(xspacing, yspacing);
		}
		else if (score == 9) {
			nineVertices(xspacing, yspacing);
		}
		break;
	}
}

void Game::zeroVertices(float xspacing, float yspacing) {
	float scaleFactor = 0.125f;
	GLfloat Vertices[] = {
	(-0.5f + xspacing)* scaleFactor, (0.5f + yspacing)* scaleFactor, 0.0f,
		(-0.5f + xspacing)* scaleFactor, (-0.5f + yspacing)* scaleFactor, 0.0f,
		(0.5f + xspacing)* scaleFactor, (-0.5f + yspacing)* scaleFactor, 0.0f,
		(0.5f + xspacing)* scaleFactor, (0.5f + yspacing)* scaleFactor, 0.0f,
		(-0.5f + xspacing)* scaleFactor, (0.5f + yspacing)* scaleFactor, 0.0f,
		(0.5f + xspacing)* scaleFactor, (0.5f + yspacing)* scaleFactor, 0.0f,
		(0.5f + xspacing)* scaleFactor, (-0.5f + yspacing)* scaleFactor, 0.0f,
	};
	memcpy(gameVertices, Vertices, sizeof(Vertices));
}
void Game::oneVertices(float xspacing, float yspacing) {
	float scaleFactor = 0.5f;
	GLfloat Vertices[] = {
		// Positions
		(-0.25f + xspacing) * scaleFactor, (0.5f + yspacing) * scaleFactor, 0.0f,   // Top-left corner
		(0.25f + xspacing) * scaleFactor, (0.5f + yspacing) * scaleFactor, 0.0f,    // Top-right corner
		(0.0f + xspacing) * scaleFactor, (0.5f + yspacing) * scaleFactor, 0.0f,     // Middle-top corner
		(0.0f + xspacing) * scaleFactor, (-0.5f + yspacing) * scaleFactor, 0.0f,    // Middle-bottom corner
		(-0.25f + xspacing) * scaleFactor, (-0.5f + yspacing) * scaleFactor, 0.0f,  // Bottom-left corner
		(0.25f + xspacing) * scaleFactor, (-0.5f + yspacing) * scaleFactor, 0.0f,   // Bottom-right corner
		(0.0f + xspacing) * scaleFactor, (0.5f + yspacing) * scaleFactor, 0.0f      // Middle-top corner (repeated to complete the shape)
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::twoVertices(float xspacing, float yspacing) {
	float scaleFactor = 0.5f;
	GLfloat Vertices[] = {
		// Positions
		(-0.25f + xspacing) * scaleFactor, (0.5f + yspacing) * scaleFactor, 0.0f,    // Top-left corner
		(0.25f + xspacing) * scaleFactor, (0.5f + yspacing) * scaleFactor, 0.0f,     // Top-right corner
		(0.25f + xspacing) * scaleFactor, (0.0f + yspacing) * scaleFactor, 0.0f,     // Middle-right corner
		(-0.25f + xspacing) * scaleFactor, (0.0f + yspacing) * scaleFactor, 0.0f,    // Middle-left corner
		(-0.25f + xspacing) * scaleFactor, (-0.5f + yspacing) * scaleFactor, 0.0f,   // Bottom-left corner
		(0.25f + xspacing) * scaleFactor, (-0.5f + yspacing) * scaleFactor, 0.0f,    // Bottom-right corner
		(-0.25f + xspacing) * scaleFactor, (0.0f + yspacing) * scaleFactor, 0.0f     // Middle-left corner (repeated to complete the shape)
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::threeVertices(float xspacing, float yspacing) {
	GLfloat Vertices[] = {
		// Positions
		-0.25f + xspacing, 0.5f + yspacing, 0.0f,    // Top-left corner
		0.25f + xspacing, 0.5f + yspacing, 0.0f,     // Top-right corner
		0.25f + xspacing, 0.0f + yspacing, 0.0f,     // Middle-right corner
		-0.25f + xspacing, 0.0f + yspacing, 0.0f,    // Middle-left corner
		0.25f + xspacing, -0.5f + yspacing, 0.0f,    // Bottom-right corner
		-0.25f + xspacing, -0.5f + yspacing, 0.0f,   // Bottom-left corner
		0.25f + xspacing, 0.0f + yspacing, 0.0f      // Middle-right corner (repeated to complete the shape)
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::fourVertices(float xspacing, float yspacing) {
	GLfloat Vertices[] = {
		// Positions
		-0.5f + xspacing, 0.5f + yspacing, 0.0f,    // Top-left corner
		0.0f + xspacing, 0.5f + yspacing, 0.0f,     // Top-right corner
		0.0f + xspacing, 0.0f + yspacing, 0.0f,     // Middle-right corner
		-0.5f + xspacing, 0.0f + yspacing, 0.0f,    // Middle-left corner
		0.0f + xspacing, -0.5f + yspacing, 0.0f,    // Bottom-right corner
		-0.5f + xspacing, -0.5f + yspacing, 0.0f,   // Bottom-left corner
		0.0f + xspacing, 0.0f + yspacing, 0.0f      // Middle-right corner (repeated to complete the shape)
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::fiveVertices(float xspacing, float yspacing) {
	GLfloat Vertices[] = {
		// Positions
		0.5f, 0.5f, 0.0f,    // Top-right corner
		0.0f, 0.5f, 0.0f,    // Top-left corner
		0.0f, 0.0f, 0.0f,    // Middle-left corner
		0.5f, 0.0f, 0.0f,    // Middle-right corner
		0.5f, -0.5f, 0.0f,   // Bottom-right corner
		0.0f, -0.5f, 0.0f,   // Bottom-left corner
		0.0f, 0.0f, 0.0f     // Middle-left corner (repeated to complete the shape)
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::sixVertices(float xspacing, float yspacing) {
	GLfloat Vertices[] = {
		// Positions
		0.5f, 0.5f, 0.0f,    // Top-right corner
		0.0f, 0.5f, 0.0f,    // Top-left corner
		0.0f, -0.5f, 0.0f,   // Bottom-left corner
		0.5f, -0.5f, 0.0f,   // Bottom-right corner
		0.5f, 0.0f, 0.0f,    // Middle-right corner
		0.0f, 0.0f, 0.0f,    // Middle-left corner
		0.5f, 0.0f, 0.0f     // Middle-right corner (repeated to complete the shape)
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::sevenVertices(float xspacing, float yspacing) {
	GLfloat Vertices[] = {
		// Positions
		0.0f, 0.5f, 0.0f,    // Top-left corner
		0.5f, 0.5f, 0.0f,    // Top-right corner
		0.25f, 0.5f, 0.0f,   // Top-middle corner
		0.25f, -0.5f, 0.0f,  // Bottom-middle corner
		0.25f, 0.0f, 0.0f,   // Middle corner
		0.0f, -0.5f, 0.0f,   // Bottom-left corner
		0.5f, -0.5f, 0.0f    // Bottom-right corner
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::eightVertices(float xspacing, float yspacing) {
	GLfloat Vertices[] = {
		// Positions
		0.25f, 0.5f, 0.0f,   // Top-middle corner
		0.25f, 0.0f, 0.0f,   // Middle corner
		0.0f, 0.0f, 0.0f,    // Top-left corner
		0.5f, 0.0f, 0.0f,    // Top-right corner
		0.5f, -0.5f, 0.0f,   // Bottom-right corner
		0.0f, -0.5f, 0.0f,   // Bottom-left corner
		0.25f, -0.5f, 0.0f   // Bottom-middle corner
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}
void Game::nineVertices(float xspacing, float yspacing) {
	GLfloat Vertices[] = {
		// Positions
		0.25f, 0.5f, 0.0f,   // Top-middle corner
		0.25f, 0.0f, 0.0f,   // Middle corner
		0.0f, 0.0f, 0.0f,    // Top-left corner
		0.5f, 0.0f, 0.0f,    // Top-right corner
		0.5f, -0.5f, 0.0f,   // Bottom-right corner
		0.25f, -0.5f, 0.0f,  // Bottom-middle corner
		0.0f, -0.5f, 0.0f    // Bottom-left corner
	};
	memcpy(gameVertices, Vertices, sizeof(gameVertices));
}