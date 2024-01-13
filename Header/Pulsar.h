#pragma once

#include "Enemy.h"

class Pulsar: public Enemy {
public:
    Pulsar(int x, int y, int width, int height, std::string id): Enemy(x, y, width, height, id, 200){};

    void update() override;
    void handleCollisions() override;

};