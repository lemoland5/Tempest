#include "../Header/FlipperTanker.h"
#include "../Header/Game.h"

void FlipperTanker::update() {

    if(m_MapPosition->y > 0){
        moveY(-1);
    }
    else{
        Enemy::kill();
    }

    if(Game::getInstance()->getFrameCount() % 70 == 0){
        if(rand() % 2 == 0){
            moveX(1);
        }
        else{
            moveX(-1);
        }
    }

    Enemy::update();
}

void FlipperTanker::handleCollisions() {
    if(!m_CollisionStack.empty()){
        Enemy::kill();
        m_CollisionStack.pop();
    }
}
