#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ball.h"

Ball::Ball() {
	location[0] = 0.0f;
	location[1] = 0.0f;
	velocity[0] = 0.045010f;
	velocity[1] = -0.03020f;
}

void Ball::update() {
	location[0] += velocity[0];
	location[1] += velocity[1];

	//edge detection
	if (location[0] > 1 || location[0] < -1)
		velocity[0] = -velocity[0];
	if (location[1] > 1 || location[1] < -1)
		velocity[1] = -velocity[1];
}

void Ball::render() {

}