#include "../Header/FlipperTanker.h"
#include "../Header/Game.h"
#include "../Header/Pulsar.h"

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
    m_FramesCharging++;

    if(m_FramesCharging % ZAP_PULSE_TIME_FRAMES * 2 > 0 && m_FramesCharging % ZAP_PULSE_TIME_FRAMES * 2 < ZAP_PULSE_TIME_FRAMES){
        m_TextureId = "pulsarAlt";
    }
    else{
        m_TextureId = "pulsar";
    }

    if(m_FramesCharging >= ZAP_TIME_FRAMES){
        Game::getInstance()->spawn<FlipperTanker>((int)m_pMapPosition->x,COLLISION_DISTANCE,1,1,"bullet");
        Enemy::kill();
    }
}

void Pulsar::resetZap() {
    m_isCharging = false;
    m_FramesCharging = false;
}
