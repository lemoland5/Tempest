#pragma once

#include "Enemy.h"

const int ZAP_TIME_FRAMES = 120;

class Pulsar: public Enemy {
public:
    Pulsar(int x, int y, int width, int height, std::string id): Enemy(x, y, width, height, id, 200){};

    void zap();
    void update() override;
    void resetZap();

private:
    bool m_isCharging = false;
    int m_FramesCharging = 0;

};