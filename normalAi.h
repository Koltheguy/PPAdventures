#pragma once
#include "player.h"
class NormalAi :
    public Player
{
public:
    NormalAi(PlayerSide playerSide, std::string name, glm::vec3 color)
        : Player("NormalAi", playerSide, name, color) {};
    void update() override;

};

