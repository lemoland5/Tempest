#pragma once

#include "Actor.h"

class Bullet: public Actor {
public:
    Bullet(int x, int y, int width, int height, std::string textureId): Actor(x, y, width, height, textureId){};

    Type getType() override {return TYPE_BULLET;};

    void update() override;
private:
    Type m_Type = TYPE_BULLET;
};