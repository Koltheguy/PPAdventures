#pragma once
#include "player.h"
#include "simpleAi.h"
#include "normalAi.h"

class PlayerFactory
{
public:
    static Player* createPlayer(std::string playerType, PlayerSide playerSide, std::string name, glm::vec3 color)
    {
        if (playerType == "SimpleAi")
            return new SimpleAi(playerSide, name, color);
        if (playerType == "NormalAi")
            return new NormalAi(playerSide, name, color);
        return new Player(playerType, playerSide, name, color);
    }
};