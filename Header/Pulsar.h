#pragma once

#include "Enemy.h"

const int ZAP_TIME_FRAMES = 90;
const int ZAP_PULSE_COUNT = 9;
const int ZAP_PULSE_TIME_FRAMES = ZAP_TIME_FRAMES/ZAP_PULSE_COUNT;

class Pulsar: public Enemy {
public:
    Pulsar(float x, float y, int width, int height, std::string id): Enemy(x, y, width, height, id, 200){};

    void zap();
    void update() override;

private:
    bool m_isCharging = false;
    int m_FramesCharging = 0;

};