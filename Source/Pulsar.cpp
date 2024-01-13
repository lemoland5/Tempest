#include "../Header/Pulsar.h"
#include "../Header/Game.h"

void Pulsar::update() {

    if(m_MapPosition->y > 50){
        moveY(-1);
    }
//    else{
//        Enemy::kill();
//    }

    Enemy::update();
}

void Pulsar::handleCollisions() {
    if(!m_CollisionStack.empty()){
        Enemy::kill();
        m_CollisionStack.pop();
    }
}
