#pragma once

#include <utility>

#include "Actor.h"

class Player : public Actor {
public:
    Player(int x, int y, int width, int height, std::string id): Actor(x, y, width, height, std::move(id)){};

    Type getType() override {return TYPE_PLAYER;};

    void update() override;
    void handleCollisions() override;
    void handleInput();
    void shoot();
    void kill() override;

    [[nodiscard]] int getLives() const {return m_Lives;};

private:
    int m_Lives = 1;
};