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
//        m_pMapPosition->x += 1;
//    }
//    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT)){
//        m_pMapPosition->x -= 1;
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
    Game::getInstance()->spawn<Bullet>(m_pMapPosition->x, m_pMapPosition->y, 10, 10, "bullet");
//    std::cout<<m_CollisionStack.top()<<"\n";
}

void Player::handleCollisions() {
    while(!m_CollisionStack.empty()){
        std::cout<<"I got touched \n";

        switch (m_CollisionStack.top()) {
            case TYPE_ENEMY:
                kill();
                 std::cout<<"Chinese person! \n";
                m_CollisionStack.pop();
                break;
            default:
                m_CollisionStack.pop();
                break;
        }
    }
}

void Player::kill() {
    std::cout<<"I got killed \n";
    m_Lives--;
    Game::getInstance()->setState(STATE_PAUSED);

//    if(m_Lives <= 0){
//         Game::getInstance()->setState(STATE_PAUSED);
//    }
//    Actor::kill();
}
