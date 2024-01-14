#include "../Header/Bullet.h"
#include <iostream>

void Bullet::update() {



    if(m_MapPosition->y < LINE_T_SCALE){
        moveY(3);
    }
    else{
        Actor::kill();
    }


    Actor::update();
}

void Bullet::handleCollisions() {
    while(!m_CollisionStack.empty()){
        switch (m_CollisionStack.top()) {
            case TYPE_ENEMY:
                Actor::kill();
                m_CollisionStack.pop();
                break;
            default:
                m_CollisionStack.pop();
                break;
        }
    }
}
