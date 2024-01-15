#pragma once

#include "Bullet.h"
#include "CollisionManager.h"
#include "HudManager.h"
#include "Map.h"
#include "Player.h"
#include "SDL_overload.h"
#include <string>

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 710;
const unsigned int WINDOW_CENTER_HORIZONTAL = WINDOW_WIDTH / 2;
const unsigned int WINDOW_CENTER_VERTICAL = WINDOW_HEIGHT / 2;
const std::string WINDOW_NAME = "Tempest";

enum GameState{
    STATE_MENU,
    STATE_INGAME
};

class Game {
public:
    static Game *getInstance();

    void addScore(int score);
    void resetScore();
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] Map* getMap() const;
    [[nodiscard]] int getFrameCount() const;

    bool initialise(const std::string &windowName = WINDOW_NAME, unsigned int width = WINDOW_WIDTH,
                    unsigned int height = WINDOW_HEIGHT);

    void handleInput();
    void update();
    void render();

    void updateIngame();
    void updateMenu();

    void renderIngame();
    void renderMenu();

    void NodeRepUpdate();

    void checkSpawn();

    template <class T>
    void spawn(int x, int y, int width, int height,std::string textureId) {
        Actor* tmp = new T(x, y, width, height, textureId);
        m_pActors.push_back(tmp);
    }

private:
    static Game *s_pInstance;
    Game() = default;

    void resetMenuSelection();
    void checkMenu();

    GameState m_GameState = STATE_MENU;

    int m_MenuSelected = 0;
    std::vector<MenuOption*> m_pMenuOptions;

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    Map *m_pMap;
    Player* m_pPlayer;
    std::vector<Actor*> m_pActors;
    bool m_isRunning;
    int m_FrameCount;
    int m_Score;
    std::string m_DisplayScore;
    std::vector<int> m_NodeRep;
};