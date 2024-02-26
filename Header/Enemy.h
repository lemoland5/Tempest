#pragma once

#include "Actor.h"

class Enemy: public Actor {
public:

    Enemy(int x, int y, int width, int height, std::string id, int scoreValue): Actor(x, y, width, height, id), m_ScoreValue(scoreValue){};

    void handleCollisions() override;

    virtual void kill(Type killerType);
    using Actor::kill;

    Type getType() override {return TYPE_ENEMY;};

private:
    int m_ScoreValue;

};