#include "../Header/Actor.h"
#include "../Header/Game.h"
#include "../Header/PathManager.h"
#include <utility>

void Actor::draw(SDL_Renderer* renderer) {
    PathManager::getInstance()->drawPath(renderer, m_TextureId, (int)m_pPosition->x, (int)m_pPosition->y, m_Rotation);
}

void Actor::moveX(int x) {
    m_pMapPosition->x += (float)x;

    if(m_pMapPosition->x < 0){
        m_pMapPosition->x = (float)Game::getInstance()->getMap()->getNodeCount() + m_pMapPosition->x;
    }
    if(m_pMapPosition->x == (float)Game::getInstance()->getMap()->getNodeCount()){
        m_pMapPosition->x = 0;
    }
    correctRotation();


}
void Actor::moveY(int y) {
    m_pMapPosition->y += (float)y;
}

void Actor::update() {
    handleCollisions();




    delete m_pPosition;
    m_pPosition = Game::getInstance()->getMap()->getNode((int)m_pMapPosition->x%10)->getAxis()->calculateTValuePoint((float)m_pMapPosition->y / LINE_T_SCALE);
}

Actor::Actor(float x, float y, int width, int height, std::string id): m_Width(width), m_Height(height), m_TextureId(std::move(id)){

    if(x > (float)Game::getInstance()->getMap()->getNodeCount()){
        m_pMapPosition = new Point(0,0);
    }
    else m_pMapPosition = new Point (x,y);

    m_pPosition = Game::getInstance()->getMap()->getNode((int)m_pMapPosition->x%10)->getAxis()->calculateTValuePoint((float)m_pMapPosition->y / LINE_T_SCALE);
    correctRotation();


}

void Actor::addCollision(Type type) {
    m_CollisionStack.push(type);
}

void Actor::kill() {
    m_MarkedForDeletion = true;



}

void Actor::moveXAbs(int x) {
    float difference = (float)x - m_pMapPosition->x;
    moveX((int)difference);
}

Actor::~Actor() {

    delete m_pMapPosition;
    delete m_pPosition;
}

void Actor::correctRotation() {
    m_Rotation = Game::getInstance()->getMap()->getNode((int)m_pMapPosition->x%10)->getAxis()->getAngle();
}
