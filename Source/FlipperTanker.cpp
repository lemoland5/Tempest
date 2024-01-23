#include "../Header/Flipper.h"
#include "../Header/FlipperTanker.h"
#include "../Header/Game.h"

void FlipperTanker::update() {

    if(m_pMapPosition->y > 0){
        moveY(-1);
    }
    else{
        Enemy::kill();
    }

//    if(Game::getInstance()->getFrameCount() % 70 == 0){
//        if(rand() % 2 == 0){
//            moveX(1);
//        }
//        else{
//            moveX(-1);
//        }
//    }

    Actor::update();
}

void FlipperTanker::kill() {
    Game::getInstance()->spawn<Flipper>(m_pMapPosition->x, m_pMapPosition->y + COLLISION_DISTANCE, m_Width, m_Height, "flipper");
    Game::getInstance()->spawn<Flipper>(m_pMapPosition->x, m_pMapPosition->y + COLLISION_DISTANCE + LINE_T_SCALE / 15, m_Width, m_Height, "flipper");
    Actor::kill();
}
