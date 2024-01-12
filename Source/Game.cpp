#include "../Header/Flipper.h"
#include "../Header/Fuseball.h"
#include "../Header/Game.h"
#include "../Header/MapLoader.h"
#include "../Header/TextureManager.h"
#include "../Header/EventHandler.h"
#include <cstdlib>

void Game::NodeRepUpdate() {
    for (int i = 0; i<m_NodeRep.size(); i++) {
        m_NodeRep[i] = 0;
    }
}

Game* Game::s_pInstance = nullptr;

Game* Game::getInstance() {
    if(!s_pInstance){
        s_pInstance = new Game();
    }
    return s_pInstance;
}

bool Game::initialise(const std::string& windowName, unsigned int width, unsigned int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

        m_pWindow = SDL_CreateWindow(windowName.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, SDL_WINDOW_SHOWN);
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

        m_frameCount = 0;
        m_isRunning = true;

//        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 255, 255);


//        m_pMap = new Map();


        m_pMap = new Map();

        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/player.svg","player");
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/bullet.svg","bullet");
        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/fuseball.svg","fuseball");

        std::cout<<"inited \n";

        m_pPlayer = new Player(0,15,90,90,"player");
        m_pActors.push_back(m_pPlayer);
        //m_NodeRep.max_size(NodeCount);
        m_NodeRep = {1,0,0,0};


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
    m_frameCount++;

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

    SDL_RenderPresent(m_pRenderer);
}

void Game::checkSpawn() {
    if(m_frameCount % 60 == 0){
        spawn<Flipper>(0,100,30,30,"player");
    }
    if(m_frameCount % 90 == 0) {
        spawn<Fuseball>(1,100,45,45,"fuseball");
    }
}

bool Game::isRunning() const {
    return m_isRunning;
}

Map *Game::getMap() const {
    return m_pMap;
}

int Game::getFrameCount() const {
    return m_frameCount;
}
