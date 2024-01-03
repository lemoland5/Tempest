#include "../Header/Actor.h"
#include "../Header/TextureManager.h"
#include <iostream>

void Actor::draw(SDL_Renderer* renderer) {
    TextureManager::getInstance()->draw(renderer,m_TextureId, m_Position->x, m_Position->y, m_Width, m_Height);

}
