#include "../Header/Fuseball.h"

void Fuseball::update() {
    if(m_Cycle % 2 == 1){
        if(m_MapPosition->y > 0){
            moveY(-1);
        }
        else{
            m_Cycle++;
        }
    }
    else{
        if(m_MapPosition->y < 100){
            moveY(1);
        }
        else{
            m_Cycle++;
        }
    }

    if(m_Cycle >= 3){
        Enemy::kill();
    }


    Enemy::update();
}

void Fuseball::handleCollisions() {
    if(!m_CollisionStack.empty()){
        Enemy::kill();
        m_CollisionStack.pop();

    }
}
