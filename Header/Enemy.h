#pragma once

#include "Actor.h"

class Enemy: public Actor {
public:

    Enemy(int x, int y, int width, int height, std::string id, int scoreValue): Actor(x, y, width, height, id), m_ScoreValue(scoreValue){};

    void kill() override;

    Type getType() override {return TYPE_ENEMY;};

private:
    int m_ScoreValue;

};