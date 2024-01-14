#include "../Header/Enemy.h"
#include "../Header/Game.h"




void Enemy::handleCollisions() {
    while(!m_CollisionStack.empty()){
        switch (m_CollisionStack.top()) {
            case TYPE_BULLET:
                Game::getInstance()->addScore(m_ScoreValue);
                kill();
                m_CollisionStack.pop();
                break;
            default:
                m_CollisionStack.pop();
                break;
        }
    }

}
