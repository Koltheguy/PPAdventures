#pragma once
#include "player.h"
class DonAi :
    public Player
{
public:
    DonAi(PlayerSide playerSide, std::string name, glm::vec3 color)
        : Player("DonAi", playerSide, name, color) {};
    void update() override;
private:
    //void moveToTarget(float target);
    //void calcVelocity();

};

