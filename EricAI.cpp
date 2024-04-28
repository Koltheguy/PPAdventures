#include <iostream>
#include "EricAI.h"
#include "ball.h"

void EricAI::update() {
    float targetPosition = calculatePosition();

    if (targetPosition > location + (length / 2)) {
        moveDirection = Direction::UP;
    }
    else if (targetPosition < location - (length / 2)) {
        moveDirection = Direction::DOWN;
    }
    else {
        moveDirection = Direction::NONE;
    }

    Player::update();
}

float EricAI::calculatePosition() const {
    if (ball->velocity[0] > 0) {
        float timeToReach = (location - ball->location[0]) / ball->velocity[0];
        float estimatedY = ball->location[1] + timeToReach * ball->velocity[1];
        return estimatedY;
    }
    return 0.0f;
}
