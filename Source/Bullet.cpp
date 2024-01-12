#include "../Header/Bullet.h"
#include <iostream>

void Bullet::update() {



    if(m_MapPosition->y < 100){
        moveY(3);
    }
    else{
        m_MarkedForDeletion = true;
    }


    Actor::update();
}

void Bullet::handleCollisions() {
    while(!m_CollisionStack.empty()){
        switch (m_CollisionStack.top()) {
            case TYPE_ENEMY:
                m_MarkedForDeletion = true;
                m_CollisionStack.pop();
                break;
            default:
                m_CollisionStack.pop();
                break;
        }
    }
}
