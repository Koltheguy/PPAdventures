#include <iostream>
#include "DonAi.h"
#include "ball.h"

void DonAi::update() {

    //moveDirection = Direction::UP;

    if (ball->location[0] > 0.5) {
        float y_new = ball->location[1] + ball->velocity[1];
        if (y_new < (location + length) || y_new > (location - length)) {
            if (location >= y_new) {
                moveDirection = Direction::DOWN;
            }
            else if (location < y_new) {
                moveDirection = Direction::UP;
            }
        }
        else {
            moveDirection = Direction::NONE;
        }
    }
    
    Player::update();
}