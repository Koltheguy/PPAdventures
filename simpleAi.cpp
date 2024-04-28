#include <iostream>
#include "simpleAi.h"
#include "ball.h"

void SimpleAi::update() {
    if (ball->location[1] > location + (length / 2)) {
        moveDirection = Direction::UP;
    }
    else if (ball->location[1] < location - (length / 2)) {
        moveDirection = Direction::DOWN;
    }
    else {
        moveDirection = Direction::NONE;
    }
    Player::update();
}