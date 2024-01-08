#pragma once

#include "Actor.h"

class Bullet: public Actor {
public:
    Bullet(int x, int y, int width, int height, std::string textureId): Actor(x, y, width, height, textureId){};

    void update() override;
};