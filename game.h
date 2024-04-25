#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "player.h"
#include "ball.h"
class Game
{

public:
	Game(std::string player1Type, std::string player2Type);
	void MainLoop();
	void render();

	static void getKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool getKey(int keyI);

protected:
	Ball ball;
	Player Player1;
	Player Player2;

private:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool keys[4]; //{W, S, UP, DOWN}

};

