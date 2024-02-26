#include "../Header/Enemy.h"
#include "../Header/Game.h"
#include "../Header/Particle.h"
#include "../Header/SfxManager.h"

void Enemy::handleCollisions() {
    while(!m_CollisionStack.empty()){
        switch (m_CollisionStack.top()) {
            case TYPE_BULLET:
                Game::getInstance()->addScore(m_ScoreValue);
                kill(TYPE_BULLET);
                m_CollisionStack.pop();
                break;
            case TYPE_PLAYER:
//                kill();
                m_MarkedForDeletion = true;
                m_CollisionStack.pop();
                break;
            default:
                m_CollisionStack.pop();
                break;
        }
    }
}

void Enemy::kill(Type killerType) {
    if(killerType == TYPE_BULLET){
        for(int i = 0; i < 4; i++){
            Game::getInstance()->spawn<Particle>(new Particle(m_pPosition->x, m_pPosition->y, 10, 10, "particle", new Point((rand()%11) - 4,(rand()%11) - 4), {255,0,0,255}));
        }
        std::cout<<"Playing death sound... \n";
        SfxManager::getInstance()->playSound("death");
    }
    else{
        Game::getInstance()->getPlayer()->kill();
    }
//    kill();
    Actor::kill();
}

