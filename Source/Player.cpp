#include "../Header/Bullet.h"
#include "../Header/EventHandler.h"
#include "../Header/Game.h"
#include "../Header/Player.h"
#include <iostream>

 void Player::update() {
    handleInput();


    Actor::update();
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

void Player::shoot(){
    Game::getInstance()->spawn<Bullet>(m_MapPosition->x, m_MapPosition->y, 30, 30, "bullet");
}