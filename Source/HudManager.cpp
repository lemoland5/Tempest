#include "../Header/HudManager.h"
#include <iostream>

HudManager *HudManager::s_pInstance = nullptr;

HudManager *HudManager::getInstance() {
    if(!s_pInstance){
        s_pInstance = new HudManager;
    }
    return s_pInstance;
}

void HudManager::loadFont(const std::string& path, int size, const std::string& id) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    m_pFonts[id] = font;
    if(m_pFonts[id]){

    }

}

void HudManager::drawText(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& fontId, const std::string& text, SDL_Color color){
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_pFonts[fontId], text.c_str(), color);
    SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(renderer,surfaceMessage);

    SDL_Rect destRect;
    destRect.x = x - w/2;
    destRect.y = y - h/2;
    destRect.w = w;
    destRect.h = h;

    SDL_RenderCopy(renderer, textureMessage, nullptr, &destRect);


    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(textureMessage);

}

[[maybe_unused]] void HudManager::drawText(SDL_Renderer *renderer, int x, int y, int w, int h, const std::string& fontId, const std::string& text) {
    drawText(renderer, x, y, w, h, fontId, text, {255,255,255,255});
}

void HudManager::destroy() {
    for(auto & font : m_pFonts){
        TTF_CloseFont(font.second);
    }
}

void MenuOption::draw(SDL_Renderer *renderer, int x, int y, int w, int h, const std::string& fontId) {
    if(m_isSelected){
        HudManager::getInstance()->drawText(renderer, x, y, w, h, fontId, m_Text, COLOR_TEXT_SELECTED);
    }
    else{
        HudManager::getInstance()->drawText(renderer, x, y, w, h, fontId, m_Text, COLOR_TEXT_UNSELECTED);
    }
}
