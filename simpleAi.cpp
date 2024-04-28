#include <iostream>
#include "simpleAi.h"
#include "ball.h"

void SimpleAi::update() {

    if (ball->location[1] > 0) {
        if (ball->location[1] > location + (length / 1.1)) {
            moveDirection = Direction::UP;
        }
        else if (ball->location[1] < location + (length / 4)) {
            moveDirection = Direction::DOWN;
        }
        else {
            moveDirection = Direction::NONE;
        }
    }
    else {
        if (ball->location[1] > location - (length / 4)) {
            moveDirection = Direction::UP;
        }
        else if (ball->location[1] < location - (length / 1.1)) {
            moveDirection = Direction::DOWN;
        }
        else {
            moveDirection = Direction::NONE;
        }
    }
    
    Player::update();
}