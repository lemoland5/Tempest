#include "../Header/Fuseball.h"
#include "../Header/Game.h"

void Fuseball::update() {
    if(Game::getInstance()->getFrameCount() % 5 == 0){
        m_Rotation += ROTATION_SPEED;
    }
    if(m_Cycle % 2 == 1){
        if(m_pMapPosition->y > 0){
            moveY(-2);
        }
        else{
            m_Cycle++;
        }
    }
    else{
        if(m_pMapPosition->y < LINE_T_SCALE){
            moveY(2);
        }
        else{
            m_Cycle++;
        }
    }

    if(m_Cycle >= 3){
        Enemy::kill(TYPE_NONE);
    }


    Actor::update();
}
