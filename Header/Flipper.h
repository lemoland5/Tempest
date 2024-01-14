#pragma once

#include "Enemy.h"

class Flipper: public Enemy {
public:
    Flipper(int x, int y, int width, int height, std::string id): Enemy(x, y, width, height, id, 150){};

    void update() override;
//    void handleCollisions() override;
private:
};