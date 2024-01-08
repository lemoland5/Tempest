#include "../Header/Bullet.h"
#include <iostream>

void Bullet::update() {
    if(m_MapPosition->y < 100){
        m_MapPosition->y += 3;
    }
    else{
        m_MarkedForDeletion = true;
    }
    Actor::update();
}