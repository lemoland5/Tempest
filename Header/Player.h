#pragma once

#include "Actor.h"

const int DEFAULT_LIVES = 3;
const int FIRE_DELAY_FRAMES = 60;

class Player : public Actor {
public:
    Player(float x, float y, int width, int height, std::string id): Actor(x, y, width, height, std::move(id)){};

    void setLives(int lives){m_Lives = lives;};
    Type getType() override {return TYPE_PLAYER;};

    void handleCollisions() override;
    void shoot();
    void update() override;
    void kill() override;

    [[nodiscard]] int getLives() const {return m_Lives;};

    void moveX(int x) override;

private:
    int m_Lives = DEFAULT_LIVES;
    bool m_canShoot = true;
    int m_FramesRecharging = 0;
};