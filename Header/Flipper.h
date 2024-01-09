#pragma once

#include "Actor.h"

class Flipper: public Actor {
public:
    Flipper(int x, int y, int width, int height, std::string id): Actor(x, y, width, height, id){};

    void update() override;
};