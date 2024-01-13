#include "../Header/EventHandler.h"
#include "../Header/Flipper.h"
#include "../Header/FlipperTanker.h"
#include "../Header/Fuseball.h"
#include "../Header/Game.h"
#include "../Header/HudManager.h"
#include "../Header/MapLoader.h"
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

        HudManager::getInstance()->loadFont("../Assets/AtariClassic-gry3.ttf",24,"atari");
//        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 255, 255);
//        m_pMap = new Map();

        m_pMap = new Map();


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
                if(event.key.keysym.sym == SDLK_RIGHT){
                    m_pPlayer->moveX(1);
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    m_pPlayer->moveX(-1);
                }
                if(event.key.keysym.sym == SDLK_SPACE){
                    m_pPlayer->shoot();
                }
                break;
        }
    }
//    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_W)){
//        std::cout<<"W \n";
//    }

}

void Game::update() {
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

void Game::render() {
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(m_pRenderer);

    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    // SDL_RenderCopy( /* ... */ );
//    SDL_RenderDrawLine(m_pRenderer, testLine);
//    testNode->draw(m_pRenderer);

//    TextureManager::getInstance()->draw(m_pRenderer, "player", 320, 240, 150, 150);
    m_pMap->draw(m_pRenderer);
    m_pPlayer->draw(m_pRenderer);

    for(auto & actor : m_pActors){
        actor->draw(m_pRenderer);
    }

    HudManager::getInstance()->drawText(m_pRenderer, WINDOW_CENTER_HORIZONTAL, WINDOW_CENTER_VERTICAL + 200, m_DisplayScore.length() * 100, 100, "atari", m_DisplayScore, {255,255,255});

    SDL_RenderPresent(m_pRenderer);
}

void Game::checkSpawn() {
    if(m_FrameCount % 120 == 0){
        spawn<Flipper>(rand() % m_pMap->getNodeCount(),100,60,30,"flipper");
    }
//    if(m_FrameCount % 120 == 0){
//        spawn<FlipperTanker>(rand() % m_pMap->getNodeCount(),120,80,30,"flipperTanker");
//    }
//    if(m_FrameCount % 100 == 0) {
//        spawn<Fuseball>(rand() % m_pMap->getNodeCount(),100,30,30,"fuseball");
//    }
//    if(m_FrameCount % 60 == 0){
//        spawn<Pulsar>(2,100,9,30,"pulsar");
//    }
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
