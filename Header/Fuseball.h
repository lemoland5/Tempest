#pragma once

#include "Actor.h"

class Fuseball: public Actor {
public:
    Fuseball(int x, int y, int width, int height, std::string id): Actor(x, y, width, height, id), m_Cycle(1){};

    Type getType() override {return TYPE_ENEMY;};

    void update() override;
private:
    int m_Cycle;
};