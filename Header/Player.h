#pragma once

#include "Actor.h"

class Player : public Actor {
public:
    Player(int x, int y, int width, int height, std::string id): Actor(x, y, width, height, id){};

    void update() override;

    Type getType() override {return TYPE_PLAYER;};

    void handleInput();

    void onCollide(Type type) override;

    void shoot();
private:
};