#include "../Header/HudManager.h"
#include <iostream>

HudManager *HudManager::s_pInstance = nullptr;

HudManager *HudManager::getInstance() {
    if(!s_pInstance){
        s_pInstance = new HudManager;
    }
    return s_pInstance;
}

void HudManager::loadFont(std::string path, int size, std::string id) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), 24);
    m_pFonts[id] = font;
    if(m_pFonts[id]){
        std::cout<<"font loaded \n";
    }
    else std::cout<<"font couldnt load \n";
}

void HudManager::drawText(SDL_Renderer* renderer, int x, int y, int w, int h, std::string fontId, std::string text, SDL_Color color){
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_pFonts[fontId], text.c_str(), color);
    SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(renderer,surfaceMessage);

    SDL_Rect destRect;
    destRect.x = x - w/2;
    destRect.y = y - h/2;
    destRect.w = w;
    destRect.h = h;

    SDL_RenderCopy(renderer, textureMessage, NULL, &destRect);
//    SDL_RenderCopy(renderer, textureMessage, &srcRect, &destRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(textureMessage);

}

void HudManager::drawText(SDL_Renderer *renderer, int x, int y, int w, int h, std::string fontId, std::string text) {
    drawText(renderer, x, y, w, h, fontId, text, {255,255,255,255});
}

void MenuOption::draw(SDL_Renderer *renderer, int x, int y, int w, int h, std::string fontId) {
    if(m_isSelected){
        HudManager::getInstance()->drawText(renderer, x, y, w, h, fontId, m_Text, COLOR_TEXT_SELECTED);
    }
    else{
        HudManager::getInstance()->drawText(renderer, x, y, w, h, fontId, m_Text, COLOR_TEXT_UNSELECTED);
    }
}
