#include "../Header/Actor.h"
#include "../Header/Game.h"
#include "../Header/TextureManager.h"
#include <iostream>

void Actor::draw(SDL_Renderer* renderer) {
    TextureManager::getInstance()->draw(renderer,m_TextureId, (m_Position->x - (m_Width*m_Anchor)), (m_Position->y - (m_Height*m_Anchor)), m_Width, m_Height);

}

void Actor::onCollide(Type type) {

}

void Actor::moveX(int x) {
    m_MapPosition->x += x;
}
void Actor::moveY(int y) {
    m_MapPosition->y += y;
}


void Actor::update() {
        // m_MapPosition rollback
    if(m_MapPosition->x < 0){
        m_MapPosition->x = (int)Game::getInstance()->getMap()->getNodeCount() - 1 + m_MapPosition->x;
    }
    if(m_MapPosition->x == (int)Game::getInstance()->getMap()->getNodeCount() - 1){
        m_MapPosition->x = 0;
    }

        // m_Position calculation.
    m_Position = Game::getInstance()->getMap()->getNode(m_MapPosition->x%4)->getAxis()->calculateTValuePoint((float)m_MapPosition->y / 100.0f);
}

Actor::Actor(int x, int y, int width, int height, std::string id): m_MapPosition(new Point(x,y)), m_Width(width), m_Height(height), m_TextureId(id), m_MarkedForDeletion(false) {
    m_Position = Game::getInstance()->getMap()->getNode(m_MapPosition->x%4)->getAxis()->calculateTValuePoint((float)m_MapPosition->y / 100.0f);
}