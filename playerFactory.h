#pragma once
#include "player.h"
#include "simpleAi.h"

class PlayerFactory
{
public:
    static Player* createPlayer(std::string playerType, PlayerSide playerSide, std::string name, glm::vec3 color)
    {
        if (playerType == "SimpleAI")
            return new SimpleAi(playerSide, name, color);
        return new Player(playerType, playerSide, name, color);
    }
};