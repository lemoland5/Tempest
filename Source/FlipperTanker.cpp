#include "../Header/FlipperTanker.h"
#include "../Header/Game.h"

void FlipperTanker::update() {

    if(m_MapPosition->y > 0){
        moveY(-1);
    }
    else{
        m_MarkedForDeletion = true;
    }

    if(Game::getInstance()->getFrameCount() % 70 == 0){
        if(rand() % 2 == 0){
            moveX(1);
        }
        else{
            moveX(-1);
        }
    }

    Actor::update();
}

void FlipperTanker::handleCollisions() {
    if(!m_CollisionStack.empty()){
        m_MarkedForDeletion = true;
        m_CollisionStack.pop();
    }
}
