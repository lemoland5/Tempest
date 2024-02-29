#include "../Header/Bullet.h"
#include "../Header/Game.h"
#include "../Header/SfxManager.h"
#include <iostream>

void Player::shoot(){
    if(!m_canShoot) return;

    Game::getInstance()->spawn<Bullet>((int)m_pMapPosition->x, (int)m_pMapPosition->y, 10, 10, "bullet");
    m_canShoot = false;
    m_FramesRecharging = FIRE_DELAY_FRAMES;
    SfxManager::getInstance()->playSound("player-shot");


}

void Player::handleCollisions() {

    while(!m_CollisionStack.empty()){


        switch (m_CollisionStack.top()) {
            case TYPE_ENEMY:
                kill();

                m_CollisionStack.pop();
                break;
            default:
                m_CollisionStack.pop();
                break;
        }
    }
}


void Player::kill() {

    m_Lives--;

    if(m_Lives > 0){
        Game::getInstance()->setState(STATE_PAUSED);
        SfxManager::getInstance()->playSound("player-death");
    }

    if(m_Lives <= 0){
         Game::getInstance()->setState(STATE_GAMEOVER);
        SfxManager::getInstance()->playSound("gameover");
    }

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

void Player::moveX(int x) {
    Actor::moveX(x);
    SfxManager::getInstance()->playSound("player-moveX");
}
