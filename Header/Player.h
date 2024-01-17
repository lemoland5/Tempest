#pragma once

#include "Actor.h"

class Player : public Actor {
public:
    Player(int x, int y, int width, int height, std::string id): Actor(x, y, width, height, id){};

    Type getType() override {return TYPE_PLAYER;};

    void update() override;
    void handleCollisions() override;
    void handleInput();
    void shoot();

    // TODO: delete
    double getX(){return m_Position->x;};
    double getY(){return m_Position->y;};

private:
};