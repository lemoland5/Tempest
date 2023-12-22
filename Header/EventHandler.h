#pragma once

#include <SDL.h>

class EventHandler {
public:
    bool isKeyDown(SDL_Scancode key);
    static EventHandler* getInstance();

    void update();
private:
    static EventHandler* s_pInstance;
    EventHandler(){};

    const Uint8* m_pKeyboardState;
};