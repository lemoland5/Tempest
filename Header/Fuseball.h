#pragma once

#include "Enemy.h"

const float ROTATION_SPEED = 1.5f;

class Fuseball: public Enemy {
public:
    Fuseball(float x, float y, int width, int height, std::string id): Enemy(x, y, width, height, id, 100){};

    void update() override;

private:
    int m_Cycle = 1;
};