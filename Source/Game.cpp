#include "../Header/Game.h"
#include "../Header/MapLoader.h"
#include "../Header/TextureManager.h"
#include "../Header/EventHandler.h"

Game* Game::s_pInstance = nullptr;

Game* Game::getInstance() {
    if(!s_pInstance){
        s_pInstance = new Game();
    }
    return s_pInstance;
}

bool Game::initialise(const std::string& windowName, unsigned int width, unsigned int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

        m_pWindow = SDL_CreateWindow(windowName.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

//        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 255, 255);


//        m_pMap = new Map();


        m_pMap = new Map();

        TextureManager::getInstance()->loadSvg(m_pRenderer, "../Assets/player.svg","player");



        std::cout<<"inited";

        m_pPlayer = new Player(0,0,90,90,"player");


        m_isRunning = true;
        return true;
    }
    return true;
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
                break;
        }
    }
//    if(EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_W)){
//        std::cout<<"W \n";
//    }

}

void Game::update() {
    m_pPlayer->update();
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

    SDL_RenderPresent(m_pRenderer);
}

bool Game::isRunning() const {
    return m_isRunning;
}

Map *Game::getMap() const {
    return m_pMap;
}
