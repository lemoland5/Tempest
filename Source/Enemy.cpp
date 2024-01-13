#include "../Header/Enemy.h"
#include "../Header/Game.h"


void Enemy::kill() {
    Game::getInstance()->addScore(m_ScoreValue);
    Actor::kill();
}
