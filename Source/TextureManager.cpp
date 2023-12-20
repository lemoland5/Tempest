#include "../Header/TextureManager.h"
#include <iostream>
#include <SDL_image.h>

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager *TextureManager::getInstance() {
    if(!s_pInstance) s_pInstance = new TextureManager;
    return s_pInstance;
}

bool TextureManager::loadSvg(SDL_Renderer* renderer, std::string path, std::string textureId) {
    SDL_RWops* rw = SDL_RWFromFile(path.c_str(),"r");
    SDL_Surface* surface = IMG_Load_RW(rw, 1);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    if(!texture) return false;
    m_TextureMap[textureId] = texture;
    return true;
}

SDL_Texture *TextureManager::getTexture(std::string textureId) {
    return m_TextureMap[textureId];
}

void TextureManager::draw(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height) {
    SDL_Rect sourceRect, destRect;

    sourceRect.x = sourceRect.y = 0;
    SDL_QueryTexture(m_TextureMap[textureId], NULL, NULL, &sourceRect.w, &sourceRect.h);

    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopy(renderer, m_TextureMap[textureId], &sourceRect, &destRect);
}
