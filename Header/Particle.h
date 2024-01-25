#pragma once

#include "Actor.h"

const int COLOR_FADE_STEP = 10;
const int PARTICLE_LIFETIME_FRAMES = 255 / COLOR_FADE_STEP;

class Particle: public Actor {
public:
    Particle(int x, int y, int width, int height, std::string id, Point* velocity, SDL_Color color);
    ~Particle() override;

    void draw(SDL_Renderer* renderer) override;
    void update() override;
    void kill() override;
    void handleCollisions() override;
    Type getType() override {return TYPE_PARTICLE;};

private:
    Point* m_pVelocity;
    int m_FramesAlive = 0;
    SDL_Color m_Color;
};