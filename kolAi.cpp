#include <iostream>
#include "kolAi.h"
#include "ball.h"

void KolAi::update() {
    if ((ball->velocity[0] > 0 && playerSide < 0) || (ball->velocity[0] < 0 && playerSide > 0)) { // move to middle
        moveToTarget(0.0f);
    }
    else {
        calcVelocity();
    }

    Player::update();
}

void KolAi::calcVelocity() {
    float remoteTarget = (OtherPlayer->location > 0) ? -1.0f : 1.0f;
    float xDelta = (playerSide * PLAYER_DISTANCE) - (ball->location[0] + ball->radius);
    float steps = xDelta / ball->velocity[0];
    float yLocation = ball->location[1] + steps * ball->velocity[1];

    float yLoc = ball->location[1];
    float xVel = ball->velocity[0];
    float yVel = ball->velocity[1];

    float edge = 0.0f;

    do
    {
        edge = 0.0f;
        if (yLocation < -1.0f)
            edge = -1.0f + ball->radius;
        else if (yLocation > 1.0f)
            edge = 1.0f - ball->radius;

        if (edge != 0.0f) {
            float stepsTilEdge = (edge - yLoc) / yVel;
            float edgeX = ball->location[0] + (stepsTilEdge * xVel);
            steps -= stepsTilEdge;
            yVel = -yVel;
            yLocation = edge + steps * yVel;
            yLoc = edge;
        }
    } while (edge != 0.0f);

    float dx = -playerSide * (2 * PLAYER_DISTANCE);
    float dy = remoteTarget - yLocation;

    float bounceAngle = atan2(dy, dx);
    float yDelta = length * (bounceAngle / BALL_MAX_BOUNCE);
    if (yDelta > length)
        yDelta = length;
    else if (yDelta < length)
        yDelta = -length;
    moveToTarget(yLocation + yDelta);

}

void KolAi::moveToTarget(float target) {
    if (location + PLAYER_SPEED < target) {
        moveDirection = Direction::UP;
    }
    else if (location - PLAYER_SPEED > target) {
        moveDirection = Direction::DOWN;
    }
    else {
        moveDirection = Direction::NONE;
    }
}