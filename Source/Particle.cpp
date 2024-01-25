#include "../Header/Particle.h"
#include "../Header/PathManager.h"
#include <iostream>

Particle::Particle(int x, int y, int width, int height, std::string id, Point *velocity, SDL_Color color): Actor(x, y, width, height, id), m_pVelocity(velocity),
                                                                                                           m_Color(color){
    m_pPosition->x = x;
    m_pPosition->y = y;
}

Particle::~Particle() {
    delete m_pVelocity;
//    Actor::~Actor();
}

void Particle::update() {
    m_FramesAlive++;

    if(m_Color.r - COLOR_FADE_STEP > 0){
        m_Color.r = static_cast<unsigned char>(m_Color.r - COLOR_FADE_STEP);
    }
    if(m_Color.g - COLOR_FADE_STEP > 0){
        m_Color.r = static_cast<unsigned char>(m_Color.g - COLOR_FADE_STEP);
    }
    if(m_Color.b - COLOR_FADE_STEP > 0){
        m_Color.r = static_cast<unsigned char>(m_Color.b - COLOR_FADE_STEP);
    }

    m_pPosition->x += m_pVelocity->x;
    m_pPosition->y += m_pVelocity->y;

    if(m_FramesAlive > PARTICLE_LIFETIME_FRAMES){
        kill();
    }
}

void Particle::draw(SDL_Renderer *renderer) {
    PathManager::getInstance()->drawPath(renderer, m_TextureId, m_pPosition->x, m_pPosition->y, m_Rotation, m_Color);
}

void Particle::kill() {
    m_MarkedForDeletion = true;
}

void Particle::handleCollisions() {
        while(!m_CollisionStack.empty()){
            m_CollisionStack.pop();
        }
}

