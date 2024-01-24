#pragma once

#include <utility>

#include "Actor.h"

const int DEFAULT_LIVES = 5;
//const int ZAPPER_RECHARGE_FRAMES =

class Player : public Actor {
public:
    Player(int x, int y, int width, int height, std::string id): Actor(x, y, width, height, std::move(id)){};

    void setLives(int lives){m_Lives = lives;};
    Type getType() override {return TYPE_PLAYER;};

    void update() override;
    void handleCollisions() override;
    void handleInput();
    void shoot();
    void zap();
    void kill() override;

    [[nodiscard]] int getLives() const {return m_Lives;};

private:
    int m_Lives = DEFAULT_LIVES;
    bool m_canZap = true;
    int m_FramesRecharging = 0;
};