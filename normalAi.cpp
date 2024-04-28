#include <iostream>
#include "normalAi.h"
#include "ball.h"

#include <iostream>
#include "simpleAi.h"
#include "ball.h"

void NormalAi::update() {
    if ((ball->velocity[0] > 0 && playerSide < 0) || (ball->velocity[0] < 0 && playerSide > 0)) {
        if (location + (length / 4) < 0) {
            moveDirection = Direction::UP;
        }
        else if (location - (length / 4) > 0) {
            moveDirection = Direction::DOWN;
        }
        else {
            moveDirection = Direction::NONE;
        }
    }
    else if (OtherPlayer->location > 0) {
        if (ball->location[1] > location + (length / 1.1)) {
            moveDirection = Direction::UP;
        }
        else if (ball->location[1] < location + (length / 2)) {
            moveDirection = Direction::DOWN;
        }
        else {
            moveDirection = Direction::NONE;
        }
    }
    else {
        if (ball->location[1] > location - (length / 2)) {
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