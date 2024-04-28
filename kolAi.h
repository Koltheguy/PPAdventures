#pragma once
#include "player.h"
class KolAi :
    public Player
{
public:
    KolAi(PlayerSide playerSide, std::string name, glm::vec3 color)
        : Player("KolAi", playerSide, name, color) {};
    void update() override;
private:
    void moveToTarget(float target);
    void calcVelocity();

};

