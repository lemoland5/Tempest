#include "../Header/EventHandler.h"

EventHandler* EventHandler::s_pInstance = nullptr;

EventHandler* EventHandler::getInstance() {
    if(!s_pInstance) s_pInstance = new EventHandler;
    return s_pInstance;
}

bool EventHandler::isKeyDown(SDL_Scancode key) {
    if(!m_pKeyboardState) return false;
    return m_pKeyboardState[key];
}

void EventHandler::update() {
    m_pKeyboardState = SDL_GetKeyboardState(nullptr);
}
