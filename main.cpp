#include <iostream>
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

int main()
{
	
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 600, "PPAdventures", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFW window error" << std::endl;
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

	// Create Vertex Shader Object and get its reference
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



	//// Vertices coordinates
	//GLfloat vertices[] =
	//{
	//	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	//	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	//	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	//};

	//// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	//GLuint VAO, VBO;

	//// Generate the VAO and VBO with only 1 object each
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);

	//// Make the VAO the current Vertex Array Object by binding it
	//glBindVertexArray(VAO);

	//// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//// Introduce the vertices into the VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//// Enable the Vertex Attribute so that OpenGL knows to use it
	//glEnableVertexAttribArray(0);

	//// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);



	Ball ball; // Initialize Ball object

	// Here is the vertex coordinates so we can dictate the shape of the ball
	GLfloat ballVertices[360 * 3]; // this is what makes it a circle
	const float radius = 0.025f;
	for (int i = 0; i < 360; i++) {
		float radians = glm::radians(static_cast<float>(i));
		ballVertices[i * 3] = cos(radians) * radius;
		ballVertices[i * 3 + 1] = sin(radians) * radius * (1000.0f / 600.0f);
		ballVertices[i * 3 + 2] = 0.0f;
	}

	// Create reference containers for the array and buffers objects for the vertex
	GLuint ballVAO, ballVBO;

	// Generate the ballVAO and ballVBO with only 1 object each for the ball
	glGenVertexArrays(1, &ballVAO);
	glGenBuffers(1, &ballVBO);

	// Make the ballVAO the current vertext array object by binding it
	glBindVertexArray(ballVAO);

	// Binding the ballVBO and telling the computer it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ballVertices), ballVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Game game("User", "User");

	// Handles key presses
	glfwSetKeyCallback(window, game.getKeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		game.MainLoop();

		ball.update(); // Moved update call here cause the location data was out of the scope of where I render the ball (which is this loop)

		// This will update the new vertices of the ball to match the changing location
		for (int i = 0; i < 360; i++) {
			float radians = glm::radians(static_cast<float>(i));
			ballVertices[i * 3] = cos(radians) * radius + ball.location[0];
			ballVertices[i * 3 + 1] = sin(radians) * radius * (1000.0f / 600.0f) + ball.location[1];
			ballVertices[i * 3 + 2] = 0.0f;
		}

		glBindBuffer(GL_ARRAY_BUFFER, ballVBO);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ballVertices), ballVertices); // Update buffer with new data

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(ballVAO);

		// Draw the ball using the GL_TRIANGLES_FAN primitive
		glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}