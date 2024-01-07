#include "../Header/Player.h"
#include "../Header/EventHandler.h"
#include "../Header/Game.h"
#include <iostream>
 void Player::update() {
    handleInput();
     std::cout<<m_MapPosition->x<<"\n";

     if(m_MapPosition->x < 0){
         m_MapPosition->x = (int)Game::getInstance()->getMap()->getNodeCount() + m_MapPosition->x;
     }
     if(m_MapPosition->x < 0){
         m_MapPosition->x = (int)Game::getInstance()->getMap()->getNodeCount() + m_MapPosition->x;
     }


     m_Position = Game::getInstance()->getMap()->getNode(m_MapPosition->x%4)->getAxis()->calculateTValuePoint(m_MapPosition->y);
}

void Player::draw(SDL_Renderer *renderer) {
    Actor::draw(renderer);
}

void Player::handleInput() {
//    EventHandler::getInstance()->update();

//    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT)){
//        m_MapPosition->x += 1;
//    }
//    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)){
//        m_MapPosition->x -= 1;
//    }
//
//    SDL_Event event;
//    if(SDL_PollEvent(&event)) {
//        switch (event.type) {
//            case SDL_KEYDOWN:
//                if (event.key.keysym.sym == SDLK_RIGHT)
//
//                break;
//        }
//    }

}