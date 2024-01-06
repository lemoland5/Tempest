#include "../Header/Player.h"
#include "../Header/EventHandler.h"
#include <iostream>

 void Player::update() {
    handleInput();
}

void Player::draw(SDL_Renderer *renderer) {
    Actor::draw(renderer);
}

void Player::handleInput() {
//    EventHandler::getInstance()->update();

    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT)){
        m_MapPosition->x += 2;
    }
    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)){
        m_MapPosition->x -= 2;
    }



}