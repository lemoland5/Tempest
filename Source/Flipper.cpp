#include "../Header/Flipper.h"
#include "../Header/Game.h"

void Flipper::update() {

//    m_Anchor += 0.1f;

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

//void Flipper::handleCollisions() {
//    if(!m_CollisionStack.empty()){
//        Enemy::kill();
//        m_CollisionStack.pop();
//    }
//}
