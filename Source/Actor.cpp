#include "../Header/Actor.h"
#include "../Header/TextureManager.h"
#include <iostream>

void Actor::draw(SDL_Renderer* renderer) {
    TextureManager::getInstance()->draw(renderer,m_TextureId, (m_Position->x - (m_Width*m_Anchor)), (m_Position->y - (m_Height*m_Anchor)), m_Width, m_Height);

}

void Actor::moveX(int x) {
    m_MapPosition->x += x;
}
void Actor::moveY(int y) {
    m_MapPosition->y += y;
}
