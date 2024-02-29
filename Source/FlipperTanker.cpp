#include "../Header/Flipper.h"
#include "../Header/FlipperTanker.h"
#include "../Header/Game.h"

void FlipperTanker::update() {

    if(m_pMapPosition->y > 0){
        moveY(-2);
    }
    else{
        Enemy::kill(TYPE_NONE);
    }










    Actor::update();
}

void FlipperTanker::kill(Type killerType) {



    Game::getInstance()->spawn<Flipper>((int)m_pMapPosition->x, (int)m_pMapPosition->y + COLLISION_DISTANCE, m_Width, m_Height, "flipper");
    Game::getInstance()->spawn<Flipper>((int)m_pMapPosition->x, (int)m_pMapPosition->y + COLLISION_DISTANCE + LINE_T_SCALE / 15, m_Width, m_Height, "flipper");
    Enemy::kill(killerType);
}

