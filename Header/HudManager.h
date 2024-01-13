#pragma once

#include <SDL_ttf.h>
#include <string>
#include <map>

class HudManager {
public:
    void loadFont(std::string path, int size, std::string id);
    void drawText(SDL_Renderer* renderer, int x, int y, int w, int h, std::string fontId, std::string text, SDL_Color color);
    void drawText(SDL_Renderer* renderer, int x, int y, int w, int h, std::string fontId, std::string text);

    static HudManager* getInstance();
private:
    static HudManager* s_pInstance;
    HudManager(){};

    std::map<std::string, TTF_Font*> m_pFonts;


};