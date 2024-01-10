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
        m_MarkedForDeletion = true;
    }


    Actor::update();
}
