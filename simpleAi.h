#pragma once
#include "player.h"
class SimpleAi :
    public Player
{
public:
    SimpleAi(PlayerSide playerSide, std::string name, glm::vec3 color)
        : Player("SimpleAI", playerSide, name, color) {};
    void update() override;

};

