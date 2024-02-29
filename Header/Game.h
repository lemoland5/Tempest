#pragma once

#include "Bullet.h"
#include "CollisionManager.h"
#include "HudManager.h"
#include "Map.h"
#include "Path.h"
#include "Player.h"
#include "SDL_overload.h"
#include <string>

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 710;
const unsigned int WINDOW_CENTER_HORIZONTAL = WINDOW_WIDTH / 2;
const unsigned int WINDOW_CENTER_VERTICAL = WINDOW_HEIGHT / 2;
const std::string WINDOW_NAME = "Tempest";
const std::string PATH_HIGHSCORE = "../Data/highscore.txt";

const int SCORE_QUOTA_DEFAULT = 1500;
const int SCORE_QUOTA_INCREMENT = 750;

const int TRANSITION_DURATION_FRAMES = 192; // 3.2s @ 60fps
const int TRANSITION_FLASH_DURATION_FRAMES = TRANSITION_DURATION_FRAMES / (int)(TRANSITION_COLOR_ORDER.size());

enum GameState{
    STATE_MENU,
    STATE_MENU_CREDITS,
    STATE_INGAME,
    STATE_PAUSED,
    STATE_GAMEOVER,
    STATE_TRANSITION
};

class Game {
public:
    static Game *getInstance();

    void setState(GameState state);
    void setHighScore(int highscore);
    void addScore(int score);
    void resetScore();
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] Map* getMap() const;
    [[nodiscard]] int getFrameCount() const;
    [[nodiscard]] Player* getPlayer() const;

    void loadHighScore();

    bool initialise(const std::string &windowName = WINDOW_NAME, unsigned int width = WINDOW_WIDTH,
                    unsigned int height = WINDOW_HEIGHT);
    void quit();

    void handleInput();
    void update();
    void render();

    void updateIngame();
    void updateMenu();
    void updatePaused();
    void updateGameover();
    void updateTransition();

    void renderIngame();
    void renderMenu();
    void renderCredits();
    void renderGameover();

    void NodeRepUpdate();

    void checkSpawn();
    void resetIngame();
    void cleanActors();

    void changeLevel();

    template <class T>
    void spawn(int x, int y, int width, int height,std::string textureId) {
        Actor* tmp = new T(x, y, width, height, textureId);
        m_pActors.push_back(tmp);
    }

    template <class T>
    void spawn(T* actor) {
        m_pActors.push_back(actor);
    }

private:
    static Game *s_pInstance;
    Game() = default;

    bool m_isRunning = true;

    int m_Level = 1;
    int m_CurrentQuota = SCORE_QUOTA_DEFAULT;

    int m_FrameCount = 0;
    int m_FrameCountPaused = 0;

    int m_HighScore = 0;

    void resetMenuSelection();
    void checkMenu();

    GameState m_GameState = STATE_MENU;

    int m_MenuSelected = 0;
    std::vector<MenuOption*> m_pMenuOptions;
    SDL_Color m_BackgroundColor = {0,0,0,255};

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    Map *m_pMap;
    Player* m_pPlayer;
    std::vector<Actor*> m_pActors;
    int m_Score;
    std::string m_DisplayScore;
    std::vector<int> m_NodeRep;
};