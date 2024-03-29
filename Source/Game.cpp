#include "../Header/Flipper.h"
#include "../Header/FlipperTanker.h"
#include "../Header/Fuseball.h"
#include "../Header/Game.h"
#include "../Header/PathManager.h"
#include "../Header/Pulsar.h"
#include "../Header/SfxManager.h"
#include <cstdlib>
#include <fstream>
#include <SDL_mixer.h>

Game* Game::s_pInstance = nullptr;

Game* Game::getInstance() {
    if(!s_pInstance){
        s_pInstance = new Game();
    }
    return s_pInstance;
}

bool Game::initialise(const std::string& windowName, unsigned int width, unsigned int height) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0 && TTF_Init() == 0 && Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0){
        m_pWindow = SDL_CreateWindow(windowName.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, SDL_WINDOW_SHOWN);
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

        m_pMenuOptions.push_back(new MenuOption("PLAY"));
        m_pMenuOptions.push_back(new MenuOption("CREDITS"));
        m_pMenuOptions.push_back(new MenuOption("QUIT"));

        HudManager::getInstance()->loadFont("../Assets/AtariClassic-gry3.ttf",36,"atari");
        m_pMap = new Map();


        PathManager::getInstance()->loadPath("../Assets/player.path", "player");
        PathManager::getInstance()->loadPath("../Assets/pulsar.path", "pulsar");
        PathManager::getInstance()->loadPath("../Assets/pulsarAlt.path", "pulsarAlt");
        PathManager::getInstance()->loadPath("../Assets/flipper.path", "flipper");
        PathManager::getInstance()->loadPath("../Assets/flipperTanker.path", "flipperTanker");
        PathManager::getInstance()->loadPath("../Assets/fuseball.path", "fuseball");
        PathManager::getInstance()->loadPath("../Assets/bullet.path", "bullet");
        PathManager::getInstance()->loadPath("../Assets/particle.path", "particle");

        SfxManager::getInstance()->loadSound("../Assets/player-shot.wav", "player-shot");
        SfxManager::getInstance()->loadSound("../Assets/enemy-death.wav", "enemy-death");
        SfxManager::getInstance()->loadSound("../Assets/gameover.wav", "gameover");
        SfxManager::getInstance()->loadSound("../Assets/player-death.wav", "player-death");
        SfxManager::getInstance()->loadSound("../Assets/level-change.wav", "level-change");
        SfxManager::getInstance()->loadSound("../Assets/player-moveX.wav", "player-moveX");
        SfxManager::getInstance()->loadSound("../Assets/menu-change.wav", "menu-change");
        SfxManager::getInstance()->loadSound("../Assets/menu-select.wav", "menu-select");
        SfxManager::getInstance()->loadSound("../Assets/pulsar-charge.wav", "pulsar-charge");
        SfxManager::getInstance()->loadSound("../Assets/pulsar-shot.wav", "pulsar-shot");


        m_pPlayer = new Player(0,0,30,30,"player");
        m_pActors.push_back(m_pPlayer);

        resetScore();
        loadHighScore();

        //m_NodeRep.max_size(NodeCount);
        m_NodeRep = {1,0,0,0,0,0,0,0,0,0};




        m_isRunning = true;


        return true;
    }
    return false;
}


void Game::handleInput() {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(m_GameState != STATE_GAMEOVER){
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        m_isRunning = false;
                    }
                }
                if(m_GameState == STATE_INGAME){
                    if(event.key.keysym.sym == SDLK_RIGHT){
                        m_pPlayer->moveX(1);
                    }
                    if(event.key.keysym.sym == SDLK_LEFT){
                        m_pPlayer->moveX(-1);
                    }
                    if(event.key.keysym.sym == SDLK_SPACE){
                        m_pPlayer->shoot();
                    }
                }

                if(m_GameState == STATE_MENU){
                    if(event.key.keysym.sym == SDLK_UP){
                        m_MenuSelected--;
                        SfxManager::getInstance()->playSound("menu-change");
                    }
                    if(event.key.keysym.sym == SDLK_DOWN){
                        m_MenuSelected++;
                        SfxManager::getInstance()->playSound("menu-change");
                    }
                    if(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN){
                        checkMenu();
                        SfxManager::getInstance()->playSound("menu-select");
                        break;
                    }
                }

                if(m_GameState == STATE_MENU_CREDITS){
                    if(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN){
                        setState(STATE_MENU);
                        SfxManager::getInstance()->playSound("menu-select");
                    }
                }

                if(m_GameState == STATE_GAMEOVER){
                    if(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN){
                        setState(STATE_INGAME);
                    }
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        setState(STATE_MENU);
                    }
                }

                break;
        }
    }




}

void Game::update() {
    m_FrameCount++;

    switch (m_GameState) {
        case STATE_MENU_CREDITS:
        case STATE_MENU:
            updateMenu();
            break;
        case STATE_INGAME:
            updateIngame();
            break;
        case STATE_PAUSED:
            updatePaused();
            break;
        case STATE_GAMEOVER:
            updateGameover();
            break;
        case STATE_TRANSITION:
            updateTransition();
            break;
    }
}

void Game::updateIngame() {
    m_pPlayer->update();

    CollisionManager::ObjectsColliding<Actor>(m_NodeRep, m_pActors);

    NodeRepUpdate();

    for(int i = 0; i < m_pActors.size(); i++){
        m_pActors[i]->update();
        m_NodeRep[(size_t)m_pActors[i]->getMapPosition()->x]++;
        if(m_pActors[i]->isMarkedForDeletion()) {
            m_NodeRep[(size_t)m_pActors[i]->getMapPosition()->x]--;
            delete m_pActors[i];

            m_pActors.erase(m_pActors.begin() + i);
        }
    }

    checkSpawn();

    if(m_Score >= m_CurrentQuota){
        changeLevel();
    }
}

void Game::updateMenu() {



    if(m_MenuSelected < 0) m_MenuSelected = (int)m_pMenuOptions.size() - 1;
    if(m_MenuSelected >= m_pMenuOptions.size()) m_MenuSelected = 0;

    resetMenuSelection();
    m_pMenuOptions[m_MenuSelected]->setSelected(true);

}

void Game::updatePaused() {
    m_FrameCountPaused++;
    if(m_FrameCountPaused % 50 > 0 && m_FrameCountPaused % 50 < 25){
        m_BackgroundColor = {127,127,127,255};
    }
    else{
        m_BackgroundColor = {0,0,0,255};
    }
    if(m_FrameCountPaused >= 150){
        resetIngame();
        m_GameState = STATE_INGAME;
    }
}

void Game::updateGameover(){
    m_FrameCountPaused++;
}

void Game::updateTransition() {
    m_FrameCountPaused++;
    int currentColor = floor(m_FrameCountPaused / TRANSITION_FLASH_DURATION_FRAMES);
    if(currentColor > TRANSITION_COLOR_ORDER.size() - 1){
        currentColor -= 1;
    }

    m_pMap->setColor(TRANSITION_COLOR_ORDER[currentColor]);

    if(m_FrameCountPaused >= TRANSITION_DURATION_FRAMES){
        m_GameState = STATE_INGAME;
    }
}



void Game::render() {

    SDL_SetRenderDrawColor(m_pRenderer, m_BackgroundColor);
    SDL_RenderClear(m_pRenderer);
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    switch (m_GameState) {
        case STATE_MENU:
            renderMenu();
            break;
        case STATE_MENU_CREDITS:
            renderCredits();
            break;
        case STATE_GAMEOVER:
            renderGameover();
            break;
        default:
            renderIngame();
            break;
    }

    SDL_RenderPresent(m_pRenderer);
}


void Game::renderMenu() {
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, 45, WINDOW_WIDTH, 100, "atari", "TEMPEST MMXXIV", COLOR_TEXT_SELECTED);

    for(int i = 0; i < m_pMenuOptions.size(); i++){
        m_pMenuOptions[i]->draw(m_pRenderer, WINDOW_CENTER_HORIZONTAL, (int)WINDOW_CENTER_VERTICAL + (100 * i) - 80, 300, 100, "atari");
    }

    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_HEIGHT - 50, WINDOW_WIDTH, 100, "atari", "HIGH SCORE: " + std::to_string(m_HighScore), COLOR_TEXT_SELECTED);

}

void Game::renderIngame() {
    m_pMap->draw(m_pRenderer);
    m_pPlayer->draw(m_pRenderer);

    for(int i = 0; i < m_pActors.size(); i++){
        m_pActors[i]->draw(m_pRenderer);
    }

    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 175, (int)m_DisplayScore.length() * 100, 100, "atari", m_DisplayScore, {255,255,255});

    for(int i = 0; i < m_pPlayer->getLives(); i++) {
        PathManager::getInstance()->drawPath(m_pRenderer, "player", (int)WINDOW_CENTER_HORIZONTAL - 300 + 40 + (i * 102),
                                             WINDOW_CENTER_VERTICAL + 175 + 100);
    }


}



void Game::checkSpawn() {
    if(m_Level <= 1){
        if(m_FrameCount % 130 == 0){
            spawn<Flipper>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipper");
        }
    }
    if(m_Level == 2){
        if(m_FrameCount % 130 == 0){
            spawn<Flipper>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipper");
        }
        if(m_FrameCount % 280 == 0){
            spawn<FlipperTanker>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipperTanker");
        }
    }
    if(m_Level == 3){
        if(m_FrameCount % 243 == 0){
            spawn<Flipper>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipper");
        }
        if(m_FrameCount % 367 == 0){
            spawn<FlipperTanker>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipperTanker");
        }
        if(m_FrameCount % 312 == 0){
            spawn<Fuseball>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"fuseball");
        }
    }
    if(m_Level == 4){
        if(m_FrameCount % 279 == 0){
            spawn<Flipper>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipper");
        }
        if(m_FrameCount % 411 == 0){
            spawn<FlipperTanker>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipperTanker");
        }
        if(m_FrameCount % 310 == 0){
            spawn<Fuseball>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"fuseball");
        }
        if(m_FrameCount % 449 == 0){
            spawn<Pulsar>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"pulsar");
        }
    }
    if(m_Level >= 5){
        if(m_FrameCount % 279 - (int)(1.8f * (float)m_Level) == 0){
            spawn<Flipper>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipper");
        }
        if(m_FrameCount % 412 - (int)(1.3f * (float)m_Level) == 0){
            spawn<FlipperTanker>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipperTanker");
        }
        if(m_FrameCount % 250 - (int)(1.9f * (float)m_Level) == 0){
            spawn<Fuseball>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"fuseball");
        }
        if(m_FrameCount % 509 - (int)(2.1f * (float)m_Level) == 0){
            spawn<Pulsar>(rand() % (int)m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"pulsar");
        }
    }


}

void Game::resetIngame() {
    m_pPlayer->moveXAbs(0);



    cleanActors();

}

void Game::NodeRepUpdate() {
    for (int & i : m_NodeRep) {
        i = 0;
    }
}

bool Game::isRunning() const {
    return m_isRunning;
}

Map *Game::getMap() const {
    return m_pMap;
}

int Game::getFrameCount() const {
    return m_FrameCount;
}

void Game::addScore(int score) {
    m_Score += score;

    std::string prefix;

    for(int i = 0; i < 4 - log10(m_Score) + 1; i++){
        prefix += "0";
    }

    m_DisplayScore = prefix + std::to_string(m_Score);

}

void Game::resetScore() {
    m_Score = 0;
    m_DisplayScore = "000000";
}

void Game::resetMenuSelection() {
    for(int i = 0; i < m_pMenuOptions.size(); i++){
        m_pMenuOptions[i]->setSelected(false);
    }
}

void Game::checkMenu() {
    switch(m_MenuSelected){
        case 0:
            setState(STATE_INGAME);
            break;
        case 1:
            setState(STATE_MENU_CREDITS);
            break;
        case 2:
            m_isRunning = false;
            break;
    }
}

void Game::setState(GameState state) {
    switch (state){
        case STATE_INGAME:
            m_pPlayer->setLives(DEFAULT_LIVES);
            resetScore();
            m_GameState = state;
            break;
        case STATE_TRANSITION:
            cleanActors();
            m_GameState = state;
            m_FrameCountPaused = 0;
            SfxManager::getInstance()->playSound("level-change");
            break;
        case STATE_GAMEOVER:
            if(m_Score > m_HighScore){
                setHighScore(m_Score);
            }
            cleanActors();
        case STATE_PAUSED:
            m_FrameCountPaused = 0;
        default:
            m_GameState = state;
    }
}

void Game::quit() {
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    HudManager::getInstance()->destroy();
    PathManager::getInstance()->destroy();
}

void Game::renderGameover() {
    if(m_FrameCountPaused % 50 > 0 && m_FrameCountPaused % 50 < 25 && m_FrameCountPaused < 150){

        HudManager::getInstance()->drawText(m_pRenderer,WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL, WINDOW_WIDTH, 200, "atari", "GAME OVER!", COLOR_TEXT);
    }
    if(m_FrameCountPaused >= 150){


        HudManager::getInstance()->drawText(m_pRenderer,WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL - 200, WINDOW_WIDTH, 140, "atari", "SCORE: " + m_DisplayScore, COLOR_TEXT);
        HudManager::getInstance()->drawText(m_pRenderer,WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL, WINDOW_WIDTH - 300, 70, "atari", "[ESC] - MAIN MENU", COLOR_TEXT);
        HudManager::getInstance()->drawText(m_pRenderer,WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 170, WINDOW_WIDTH - 150, 70, "atari", "[SPACE/ENTER] - PLAY AGAIN", COLOR_TEXT);
    }
}

void Game::cleanActors() {
    while(m_pActors.size() > 1){
        m_pActors.pop_back();
    }
}

void Game::loadHighScore() {
    std::ifstream file;
    std::string line;
    file.open(PATH_HIGHSCORE);

    if ( file.is_open() ) {
        std::getline(file,line);
        m_HighScore = std::stoi(line);
    }
    file.close();
}

void Game::setHighScore(int highscore) {
    m_HighScore = highscore;

    std::ofstream file;
    file.open(PATH_HIGHSCORE);
    file << std::to_string(highscore);
    file.close();
}

void Game::changeLevel() {
    m_Level++;
    m_CurrentQuota += SCORE_QUOTA_DEFAULT + SCORE_QUOTA_INCREMENT;  // 1500 -> 1800 -> 2100 -> 2400

    setState(STATE_TRANSITION);
}

Player *Game::getPlayer() const {
    return m_pPlayer;
}

void Game::renderCredits() {
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, 45, WINDOW_WIDTH, 100, "atari", "TEMPEST MMXXIV", COLOR_TEXT_SELECTED);


    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL - 225, WINDOW_WIDTH, 35, "atari", "FOR MOTOROLA SCIENCE CUP", COLOR_TEXT_SELECTED);
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL - 160, WINDOW_WIDTH - 100, 35, "atari", "PROGRAMMING:", COLOR_TEXT_CREDITS);
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL - 120, WINDOW_WIDTH - 100, 35, "atari", "PRZEMYSLAW SMYCZYK", COLOR_TEXT_CREDITS);
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL - 90, WINDOW_WIDTH - 100, 35, "atari", "MAKSYMILIAN DYNUS", COLOR_TEXT_CREDITS);

    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL - 35, WINDOW_WIDTH - 100, 35, "atari", "SOUND DESIGN:", COLOR_TEXT_CREDITS);
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL - 5, WINDOW_WIDTH - 100, 35, "atari", "BARTOSZ BARTOCHA", COLOR_TEXT_CREDITS);

    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 50, WINDOW_WIDTH - 100, 35, "atari", "ARTWORK:", COLOR_TEXT_CREDITS);
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 80, WINDOW_WIDTH - 100, 35, "atari", "PRZEMYSLAW SMYCZYK", COLOR_TEXT_CREDITS);

    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 145, WINDOW_WIDTH - 100, 35, "atari", "ATARI CLASSIC FONT BY MARK SIMONSON", COLOR_TEXT_SELECTED);
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 180, WINDOW_WIDTH - 100, 35, "atari", "MADE USING SDL2", COLOR_TEXT_SELECTED);
    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 215, WINDOW_WIDTH - 100, 35, "atari", "MADE @ ZSTI GLIWICE", COLOR_TEXT_SELECTED);


    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_HEIGHT - 50, WINDOW_WIDTH, 100, "atari", "[SPACE/ENTER] - MAIN MENU", COLOR_TEXT_SELECTED);

}


