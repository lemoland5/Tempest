#include "../Header/Game.h"

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
        testLine = new Line(100, 100, 200, 200);
        testNode = new Node(new Point(100, 130), new Point(225, 109), new Point(200, 200), new Point(311, 195));


        m_pMap = new Map();





        m_isRunning = true;
        return true;
    }
    return true;
}

void Game::handleInput() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                m_isRunning = false;
            }
            break;
    }
}

void Game::update() {
    /* ... */
}

void Game::render() {
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(m_pRenderer);

    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    // SDL_RenderCopy( /* ... */ );
//    SDL_RenderDrawLine(m_pRenderer, testLine);
//    testNode->draw(m_pRenderer);

    m_pMap->draw(m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

bool Game::isRunning() const {
    return m_isRunning;
}
