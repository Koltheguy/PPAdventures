#include "ball.h"

Ball::Ball() {
	location[0] = 0.0f;
	location[1] = 0.0f;
	velocity[0] = 1.24356f;
	velocity[1] = -1.213456f;
}

void Ball::update() {
	location[0] += velocity[0];
	location[1] += velocity[1];

	//edge detection
	if (location[0] > 50 || location[0] < -50)
		velocity[0] = -velocity[0];
	if (location[1] > 50 || location[1] < -50)
		velocity[1] = -velocity[1];
}