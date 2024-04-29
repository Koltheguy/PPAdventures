#pragma once

#include "player.h"
#include "ball.h"

class EricAI : public Player {
public:
    EricAI(PlayerSide playerSide, std::string name, glm::vec3 color)
        : Player("EricAI", playerSide, name, color) {}
    void update() override;

private:
    float calculatePosition() const;
    void moveTowards(float targetPosition);
};


