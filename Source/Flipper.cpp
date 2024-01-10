#include "../Header/Flipper.h"
#include "../Header/Game.h"

void Flipper::update() {

    if(m_MapPosition->y > 0){
        moveY(-1);
    }
    else{
        m_MarkedForDeletion = true;
    }

    if(Game::getInstance()->getFrameCount() % 90 == 0){
        if(rand() % 2 == 0){
            moveX(1);
        }
        else{
            moveX(-1);
        }
    }

    Actor::update();
}
