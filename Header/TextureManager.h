#pragma once

#include <map>
#include <SDL.h>
#include <string>

class TextureManager {
public:
    static TextureManager* getInstance();

    SDL_Texture* getTexture(std::string textureId);

    bool loadSvg(SDL_Renderer* renderer, std::string path, std::string textureId);
    void draw(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height);
private:
    static TextureManager* s_pInstance;
    std::map<std::string, SDL_Texture*> m_TextureMap;
    TextureManager(){};
};