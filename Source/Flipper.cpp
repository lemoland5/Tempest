#include "../Header/Flipper.h"

void Flipper::update() {

    if(m_MapPosition->y > 0){
        moveY(-3);
    }
    else{
        m_MarkedForDeletion = true;
    }

    Actor::update();
}
