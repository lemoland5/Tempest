#include "../Header/Bullet.h"
#include "../Header/EventHandler.h"
#include "../Header/Game.h"
#include "../Header/Player.h"
#include <iostream>

void Player::shoot(){
    if(!m_canShoot) return;
    Game::getInstance()->spawn<Bullet>(m_pMapPosition->x, m_pMapPosition->y, 10, 10, "bullet");
    m_canShoot = false;
    m_FramesRecharging = FIRE_DELAY_FRAMES;
}

void Player::handleCollisions() {
//    std::cout<<m_CollisionStack.size()<<"\n";
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

    if(m_Lives <= 0){
         Game::getInstance()->setState(STATE_GAMEOVER);
    }
//    Actor::kill();
}

void Player::update() {
    if(m_FramesRecharging > 0){
        --m_FramesRecharging;
    }
    else{
        m_canShoot = true;
    }

    Actor::update();
}
