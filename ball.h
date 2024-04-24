#pragma once
#include <glad/glad.h>
class Ball
{
public:
	Ball();
	float location[2];
	float velocity[2];
	void update();
	GLuint render(GLFWwindow* window);
};

