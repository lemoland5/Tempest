#include "../Header/EventHandler.h"
#include "../Header/Flipper.h"
#include "../Header/FlipperTanker.h"
#include "../Header/Fuseball.h"
#include "../Header/Game.h"
#include "../Header/MapLoader.h"
#include "../Header/PathManager.h"
#include "../Header/Pulsar.h"
#include "../Header/TextureManager.h"
#include <cstdlib>

Game* Game::s_pInstance = nullptr;

Game* Game::getInstance() {
    if(!s_pInstance){
        s_pInstance = new Game();
    }
    return s_pInstance;
}

bool Game::initialise(const std::string& windowName, unsigned int width, unsigned int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0){

        m_pWindow = SDL_CreateWindow(windowName.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, SDL_WINDOW_SHOWN);
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

        m_FrameCount = 0;
        m_isRunning = true;
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/bullet.svg","bullet");
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/flipper.svg","flipper");
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/flipperTanker.svg","flipperTanker");
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/fuseball.svg","fuseball");
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/player.svg","player");
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/pulsar.svg","pulsar");

        m_pMenuOptions.push_back(new MenuOption("PLAY"));
        m_pMenuOptions.push_back(new MenuOption("QUIT"));

        HudManager::getInstance()->loadFont("../Assets/AtariClassic-gry3.ttf",24,"atari");
//        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 255, 255);
//        m_pMap = new Map();

        m_pMap = new Map();

//        TestPath = new Path();


        PathManager::getInstance()->loadPath("../Assets/player.path", "player");
        PathManager::getInstance()->loadPath("../Assets/player.path", "pulsar");
        PathManager::getInstance()->loadPath("../Assets/player.path", "flipper");
        PathManager::getInstance()->loadPath("../Assets/player.path", "flipperTanker");
        PathManager::getInstance()->loadPath("../Assets/player.path", "fuseball");
        PathManager::getInstance()->loadPath("../Assets/player.path", "bullet");
//        PathManager::getInstance()->loadPath("../Assets/player.path", "player");

        m_pPlayer = new Player(0,0,30,30,"player");
        m_pActors.push_back(m_pPlayer);

        resetScore();

        //m_NodeRep.max_size(NodeCount);
        m_NodeRep = {1,0,0,0};

        std::cout<<"inited \n";
        return true;
    }
    return false;
}


void Game::handleInput() {
    EventHandler::getInstance()->update();

    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    m_isRunning = false;
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
                else{
                    if(event.key.keysym.sym == SDLK_UP){
                        m_MenuSelected++;
                    }
                    if(event.key.keysym.sym == SDLK_DOWN){
                        m_MenuSelected--;
                    }
                    if(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN){
                        checkMenu();
                    }
                    if(event.key.keysym.sym == SDLK_RIGHT){
                        TestPath->rotate(1);
                    }
                    if(event.key.keysym.sym == SDLK_LEFT){
                        TestPath->rotate(-1);
                    }
                }
                break;
        }
    }
//    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_W)){
//        std::cout<<"W \n";
//    }

}

void Game::update() {
//
//    TestPath->rotate(1);
//    TestPath->moveX(1);
//    TestPath->moveY(1);

    PathManager::getInstance()->movePathXAbs("player",m_pPlayer->getX());
    PathManager::getInstance()->movePathYAbs("player",m_pPlayer->getY());

    switch (m_GameState) {
        case STATE_MENU:
            updateMenu();
            break;
        case STATE_INGAME:
            updateIngame();
            break;
    }
}

void Game::updateIngame() {
    m_FrameCount++;
//    addScore(1);

    m_pPlayer->update();

    CollisionManager::ObjectsColliding<Actor>(m_NodeRep, m_pActors);

    NodeRepUpdate();

    for(int i = 0; i < m_pActors.size(); i++){
        m_pActors[i]->update();
        m_NodeRep[m_pActors[i]->getMapPosition()->x]++;
        if(m_pActors[i]->isMarkedForDeletion()) {
            m_NodeRep[m_pActors[i]->getMapPosition()->x]--;
            delete m_pActors[i];
            m_pActors.erase(m_pActors.begin() + i);
        }
    }

    checkSpawn();
}

void Game::updateMenu() {
//    std::cout<<"updatin \n";
//    std::cout<<m_MenuSelected<<"\n";

    if(m_MenuSelected < 0) m_MenuSelected = (int)m_pMenuOptions.size() - 1;
    if(m_MenuSelected >= m_pMenuOptions.size()) m_MenuSelected = 0;

    resetMenuSelection();
    m_pMenuOptions[m_MenuSelected]->setSelected(true);
}

void Game::render() {
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(m_pRenderer);
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    // SDL_RenderCopy( /* ... */ );
//    SDL_RenderDrawLine(m_pRenderer, testLine);
//    testNode->draw(m_pRenderer);

//    TextureManager::getInstance()->draw(m_pRenderer, "player", 320, 240, 150, 150);


    switch (m_GameState) {
        case STATE_MENU:
            renderMenu();
            break;
        case STATE_INGAME:
            renderIngame();
            break;
    }

//    TestPath->draw(m_pRenderer);

    PathManager::getInstance()->drawPath(m_pRenderer, "player", 500, 100);

    SDL_RenderPresent(m_pRenderer);
}


void Game::renderMenu() {
//    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, 80, WINDOW_WIDTH, 100, "atari", "TEMPEST MMXXIV", COLOR_TEXT_SELECTED);

    for(int i = 0; i < m_pMenuOptions.size(); i++){
        m_pMenuOptions[i]->draw(m_pRenderer, WINDOW_CENTER_HORIZONTAL, (int)WINDOW_CENTER_VERTICAL + (100 * i), 300, 100, "atari");
    }


}

void Game::renderIngame() {
    m_pMap->draw(m_pRenderer);
    m_pPlayer->draw(m_pRenderer);

    for(auto & actor : m_pActors){
        actor->draw(m_pRenderer);
    }

    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 175, (int)m_DisplayScore.length() * 100, 100, "atari", m_DisplayScore, {255,255,255});
}



void Game::checkSpawn() {
//    if(m_FrameCount % 120 == 0){
//        spawn<Flipper>(rand() % m_pMap->getNodeCount(),LINE_T_SCALE,60,30,"flipper");
//    }

    if(m_FrameCount % 120 == 0){
        spawn<Flipper>(0,LINE_T_SCALE,60,30,"flipper");
    }

    if(m_FrameCount % 120 == 0){
        spawn<FlipperTanker>(rand() % m_pMap->getNodeCount(),LINE_T_SCALE,80,30,"flipperTanker");
    }

//    if(m_FrameCount % 120 == 0){
//        spawn<FlipperTanker>(0,LINE_T_SCALE,80,30,"flipperTanker");
//    }
//    if(m_FrameCount % 100 == 0) {
//        spawn<Fuseball>(rand() % m_pMap->getNodeCount(),LINE_T_SCALE,30,30,"fuseball");
//    }
    if(m_FrameCount % 60 == 0){
        spawn<Pulsar>(2,LINE_T_SCALE,9,30,"pulsar");
    }
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
//    std::cout<<m_DisplayScore<<"\n";
}

void Game::resetScore() {
    m_Score = 0;
    m_DisplayScore = "000000";
}

void Game::resetMenuSelection() {
    for(auto & option : m_pMenuOptions){
        option->setSelected(false);
    }
}

void Game::checkMenu() {
    switch(m_MenuSelected){
        case 0:
            m_GameState = STATE_INGAME;
            break;
        case 1:
            m_isRunning = false;
            break;
    }
}

