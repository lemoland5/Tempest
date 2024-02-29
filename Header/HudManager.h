#pragma once

#include <SDL_ttf.h>
#include <string>
#include <map>
#include <utility>

const int SELECTED_ALPHA = 255;
const int UNSELECTED_ALPHA = (int)(SELECTED_ALPHA * 0.5f);

const SDL_Color COLOR_TEXT = {
        255,
        255,
        255,
        255
};

const SDL_Color COLOR_TEXT_SELECTED = {
        255,
        255,
        255,
        SELECTED_ALPHA
};

const SDL_Color COLOR_TEXT_UNSELECTED = {
        255,
        255,
        255,
        UNSELECTED_ALPHA
};

const SDL_Color COLOR_TEXT_CREDITS = {
        180,
        160,
        255,
        SELECTED_ALPHA
};

class HudManager {
public:
    void loadFont(const std::string& path, int size, const std::string& id);
    void drawText(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& fontId, const std::string& text, SDL_Color color);

    [[maybe_unused]] void drawText(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& fontId, const std::string& text);

    void destroy();


    static HudManager* getInstance();
private:
    static HudManager* s_pInstance;
    HudManager(){};

    std::map<std::string, TTF_Font*> m_pFonts;
};

class MenuOption{
public:

    explicit MenuOption(std::string text): m_Text(std::move(text)) {};
    void draw(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& fontId);

    void setSelected(bool selection){m_isSelected = selection;};
    [[nodiscard]] bool isSelected() const {return m_isSelected;};
    [[nodiscard]] std::string getText() const {return m_Text;};

private:
    std::string m_Text;
    bool m_isSelected = false;
};