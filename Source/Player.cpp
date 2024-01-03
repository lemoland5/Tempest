#include "../Header/Player.h"
#include "../Header/EventHandler.h"
#include <iostream>

 void Player::update() {
    handleInput();
}

void Player::draw(SDL_Renderer *renderer) {
    Actor::draw(renderer);
    std::cout<<m_TextureId<<": "<<m_Position->x<<", "<<m_Position->y<<"\n";
}

void Player::handleInput() {
    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT)){
        ++m_Position->x;
    }
    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)){
        --m_Position->x;
    }
}