#pragma once

#include "Enemy.h"

class Fuseball: public Enemy {
public:
    Fuseball(int x, int y, int width, int height, std::string id): Enemy(x, y, width, height, id, 100), m_Cycle(1){};

    void update() override;
    void handleCollisions() override;

private:
    int m_Cycle;
};