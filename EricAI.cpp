#include "EricAI.h"
#include "ball.h"

void EricAI::update() {
    float targetPosition = calculatePosition();

    moveTowards(targetPosition);

    Player::update();
}

float EricAI::calculatePosition() const {
    if (ball->velocity[0] < 0) {
        float timeToIntersect = (location - ball->location[0]) / ball->velocity[0];
        float estimatedY = ball->location[1] + timeToIntersect * ball->velocity[1];

        return std::max(-0.5f + length / 2, std::min(0.5f - length / 2, estimatedY));
    }
    return location;
}

void EricAI::moveTowards(float targetPosition) {
    if (targetPosition > location) {
        moveDirection = Direction::UP;
    }
    else if (targetPosition < location) {
        moveDirection = Direction::DOWN;
    }
    else {
        moveDirection = Direction::NONE;
    }
}
