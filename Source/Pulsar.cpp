#include "../Header/Pulsar.h"
#include "../Header/Game.h"

void Pulsar::update() {

    if(m_MapPosition->y > 50){
        moveY(-1);
    }
//    else{
//        m_MarkedForDeletion = true;
//    }

    Actor::update();
}

void Pulsar::handleCollisions() {
    if(!m_CollisionStack.empty()){
        m_MarkedForDeletion = true;
        m_CollisionStack.pop();
    }
}
