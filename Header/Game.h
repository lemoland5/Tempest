#pragma once

#include "Map.h"
#include "SDL_overload.h"
#include <string>

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;
const std::string WINDOW_NAME = "Tempest";

class Game {
public:
    static Game* getInstance();
    [[nodiscard]] bool isRunning() const;

    bool initialise(const std::string& windowName = WINDOW_NAME, unsigned int width = WINDOW_WIDTH, unsigned int height = WINDOW_HEIGHT);
    void handleInput();
    void update();
    void render();



private:
    static Game* s_pInstance;
    Game(){};

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    Map* m_pMap;
    bool m_isRunning;

};