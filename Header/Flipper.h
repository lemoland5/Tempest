#pragma once

#include "Enemy.h"

const int FLIP_TIME_FRAMES = 60;
const float FLIP_ROTATION_DEGREES = 90;

class Flipper: public Enemy {
public:
    Flipper(int x, int y, int width, int height, std::string id): Enemy(x, y, width, height, id, 150){};

    void flip();
    void resetFlip();

    void update() override;
//    void handleCollisions() override;
private:
    bool m_isFlipping = false;
    int m_FramesFlipping = 0;

    // positives for movement to the right
    // 0 for passive
    // negatives for movement to the left
    int m_FlipDestination = 0;
};