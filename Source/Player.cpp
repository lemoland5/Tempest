#include "../Header/Player.h"
#include "../Header/EventHandler.h"
#include "../Header/Game.h"
#include <iostream>

 void Player::update() {
    handleInput();
    m_Position = Game::getInstance()->getMap()->getNode(m_MapPosition->x%4)->getAxis()->calculateTValuePoint(m_MapPosition->y);
}

void Player::draw(SDL_Renderer *renderer) {
    Actor::draw(renderer);
}

void Player::handleInput() {
//    EventHandler::getInstance()->update();

    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT)){
        m_MapPosition->x += 1;
    }
    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)){
        m_MapPosition->x -= 1;
    }



}