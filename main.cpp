#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "game.h"


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\n\0";

void errorCallback(int error, const char* description) {
	std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

std::string updateWindow() {
	int player1Score = 0;
	int player2Score = 0;
	std::string score1 = std::to_string(player1Score);
	std::string score2 = std::to_string(player2Score);
	std::string name = "PPAdventures SCORE: ";
	name += score1;
	name += " - ";
	name += score2;

	return name;
}

int main()
{
	
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::string Score = updateWindow();

	GLFWwindow* window = glfwCreateWindow(1000, 600, Score.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "GLFW window error" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 1000, 600);

	// background color ffbbc3
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// Create Vertex Shader Object and get its freference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	int limit;
	std::string player1;
	std::string player2;
	std::cout << "Input Limit: ";
	std::cin >> limit;
	std::cout << "Player Options (Default User): User, SimpleAi, NormalAi, KolAi, DonAi, EricAi" << std::endl;
	std::cout << "Input Player 1: ";
	std::cin >> player1;
	std::cout << "Input Player 2: ";
	std::cin >> player2;

	Game game(player1, player2, limit);

	// Handles key presses
	glfwSetKeyCallback(window, game.getKeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


	// Main Loop
	while (!glfwWindowShouldClose(window))
	{

		
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);

		game.MainLoop(window);
		// Swap the back buffer with the front buffer

		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}