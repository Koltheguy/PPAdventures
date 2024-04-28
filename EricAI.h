#pragma once
#ifndef SIMPLE_AI_H
#define SIMPLE_AI_H

#include "player.h"
#include "ball.h"

class EricAI : public Player {
public:
    EricAI(std::string playerType, PlayerSide side, std::string name, glm::vec3 color)
        : Player(playerType, side, name, color) {}

    void update() override;

private:
    float calculatePosition() const;
};

#endif

