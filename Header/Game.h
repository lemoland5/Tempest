#pragma once

#include "Bullet.h"
#include "CollisionManager.h"
#include "Map.h"
#include "Player.h"
#include "SDL_overload.h"
#include <string>

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;
const std::string WINDOW_NAME = "Tempest";

class Game {
public:
    static Game *getInstance();

    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] Map* getMap() const;
    [[nodiscard]] int getFrameCount() const;

    bool initialise(const std::string &windowName = WINDOW_NAME, unsigned int width = WINDOW_WIDTH,
                    unsigned int height = WINDOW_HEIGHT);

    void handleInput();
    void update();
    void render();

    void NodeRepUpdate();

    void checkSpawn();

    template <class T>
    void spawn(int x, int y, int width, int height,std::string textureId) {
        Actor* tmp = new T(x, y, width, height, textureId);
        m_pActors.push_back(tmp);
    }

private:
    static Game *s_pInstance;

    Game() {};

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    Map *m_pMap;
    Player* m_pPlayer;
    std::vector<Actor*> m_pActors;
    bool m_isRunning;
    int m_frameCount;

    std::vector<int> m_NodeRep;

};