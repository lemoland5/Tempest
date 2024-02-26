#pragma once

#include "Enemy.h"
class FlipperTanker: public Enemy {
public:
    FlipperTanker(int x, int y, int width, int height, std::string id): Enemy(x, y, width, height, id, 100){};

    void kill(Type killerType);

    void update() override;


};