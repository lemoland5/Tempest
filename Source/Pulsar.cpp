#include "../Header/Fuseball.h"
#include "../Header/Game.h"
#include "../Header/Pulsar.h"
#include "../Header/SfxManager.h"

void Pulsar::update() {

    if(m_pMapPosition->y > LINE_T_SCALE / 2){
        moveY(-1);
    }
    else{
        if(!m_isCharging){
            m_isCharging = true;
        }
        else{
            zap();
        }
    }

    Actor::update();
}

void Pulsar::zap() {
    if(m_FramesCharging == 0){
        SfxManager::getInstance()->playSound("pulsar-charge");
    }

    m_FramesCharging++;

    if(m_FramesCharging % ZAP_PULSE_TIME_FRAMES * 2 > 0 && m_FramesCharging % ZAP_PULSE_TIME_FRAMES * 2 < ZAP_PULSE_TIME_FRAMES){
        m_TextureId = "pulsarAlt";
    }
    else{
        m_TextureId = "pulsar";
    }

    if(m_FramesCharging >= ZAP_TIME_FRAMES){
        Game::getInstance()->spawn<Fuseball>((int)m_pMapPosition->x,COLLISION_DISTANCE,1,1,"fuseball");
        SfxManager::getInstance()->playSound("pulsar-shot");
        Enemy::kill();
    }
}