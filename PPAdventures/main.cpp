#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, 1000, 600);

	// background color ffbbc3
	glClearColor(1.0f, 0.73f, 0.76f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// All GLFW events
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}