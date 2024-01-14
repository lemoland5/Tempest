#include "../Header/Pulsar.h"
#include "../Header/Game.h"

void Pulsar::update() {

    if(m_MapPosition->y > LINE_T_SCALE / 2){
        moveY(-1);
    }
//    else{
//        Enemy::kill();
//    }

    Enemy::update();
}

void Pulsar::handleCollisions() {
Enemy::handleCollisions();
}
