#pragma once

#include "Actor.h"

class Pulsar: public Actor {
public:
    Pulsar(int x, int y, int width, int height, std::string id): Actor(x, y, width, height, id){};

    Type getType() override {return TYPE_ENEMY;};

    void update() override;
    void handleCollisions() override;

};