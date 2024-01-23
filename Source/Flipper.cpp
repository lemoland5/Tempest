#include "../Header/Flipper.h"
#include "../Header/Game.h"

void Flipper::update() {

//    m_Anchor += 0.1f;

    if(m_pMapPosition->y > 0){
        moveY(-1);
    }
    else{
        Enemy::kill();
    }

    if(Game::getInstance()->getFrameCount() % 70 == 0 && rand() % 2 == 0 && !m_isFlipping){
        m_isFlipping = true;
        if(rand() % 2 == 0){
            m_FlipDestination = 1;
        }
        else{
            m_FlipDestination = -1;
        }
    }
    if(m_isFlipping){
        flip();
    }

    Enemy::update();
}

void Flipper::flip() {
    m_isFlipping = true;
    m_FramesFlipping++;

    if(m_FlipDestination > 0){
        m_Rotation += FLIP_ROTATION_DEGREES / FLIP_TIME_FRAMES;
    }
    if(m_FlipDestination < 0){
        m_Rotation -= FLIP_ROTATION_DEGREES / FLIP_TIME_FRAMES;
    }

    if(m_FramesFlipping >= FLIP_TIME_FRAMES){
        moveX(m_FlipDestination);
        correctRotation();
        resetFlip();
    }




}

void Flipper::resetFlip() {
    m_isFlipping = false;
    m_FramesFlipping = 0;
}

