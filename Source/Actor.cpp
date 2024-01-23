#include "../Header/Actor.h"
#include "../Header/Game.h"
#include "../Header/PathManager.h"
#include <iostream>
#include <utility>

void Actor::draw(SDL_Renderer* renderer) {
//    TextureManager::getInstance()->draw(renderer,m_TextureId, (m_pPosition->x - (m_Width*m_Anchor)), (m_pPosition->y - (m_Height*m_Anchor)), m_Width, m_Height);
    PathManager::getInstance()->drawPath(renderer, m_TextureId, m_pPosition->x, m_pPosition->y, m_Rotation);
}

void Actor::moveX(int x) {
    m_pMapPosition->x += x;

    //     m_pMapPosition rollback
    if(m_pMapPosition->x < 0){
        m_pMapPosition->x = (float)Game::getInstance()->getMap()->getNodeCount() - 1 + m_pMapPosition->x;
    }
    if(m_pMapPosition->x == (float)Game::getInstance()->getMap()->getNodeCount() - 1){
        m_pMapPosition->x = 0;
    }
}
void Actor::moveY(int y) {
    m_pMapPosition->y += y;
}

void Actor::update() {
    handleCollisions();




    delete m_pPosition;     // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    m_pPosition = Game::getInstance()->getMap()->getNode((int)m_pMapPosition->x%4)->getAxis()->calculateTValuePoint((float)m_pMapPosition->y / LINE_T_SCALE);
}

Actor::Actor(float x, float y, int width, int height, std::string id): m_pMapPosition(new Point(x,y)), m_Width(width), m_Height(height), m_TextureId(std::move(id)){
    m_pPosition = Game::getInstance()->getMap()->getNode((int)m_pMapPosition->x%4)->getAxis()->calculateTValuePoint((float)m_pMapPosition->y / LINE_T_SCALE);
    correctRotation();
    // std::cout<<m_Rotation<<"\n";

}

void Actor::addCollision(Type type) {
    m_CollisionStack.push(type);
}

void Actor::kill() {
    m_MarkedForDeletion = true;
}

void Actor::moveXAbs(int x) {
    float difference = x - m_pMapPosition->x;
    moveX(difference);
}

Actor::~Actor() {
    std::cout<<"ima head out \n";
    delete m_pMapPosition;
    delete m_pPosition;
}

void Actor::correctRotation() {
    m_Rotation = Game::getInstance()->getMap()->getNode((int)m_pMapPosition->x%4)->getAxis()->getAngle();
}
