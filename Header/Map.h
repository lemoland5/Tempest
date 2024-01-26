#pragma once

#include "Node.h"
#include <SDL.h>
#include <vector>

// ../Assets/tempest map transition colors.png
const SDL_Color COLOR_PURPLE = {0, 9, 155, 255};
const SDL_Color COLOR_GREY = {214, 214, 214, 255};
const SDL_Color COLOR_BLUE = {116, 133, 245, 255};
const SDL_Color COLOR_GREEN = {120, 215, 127, 255};
const SDL_Color COLOR_PINK = {172, 137, 243, 255};
const SDL_Color COLOR_GREEN_LIGHT = {179, 218, 116, 255};
const SDL_Color COLOR_SALMON = {149, 138, 125, 255};
const SDL_Color COLOR_PINK_LIGHT = {201, 137, 241, 255};
const SDL_Color COLOR_CYAN = {109, 218, 195, 255};
const SDL_Color COLOR_ORANGE = {236, 200, 97, 255};
const SDL_Color COLOR_YELLOW = {234, 223, 68, 255};
const SDL_Color COLOR_BLUE_LIGHT = {111, 178, 243, 255};

const SDL_Color COLOR_MAP_DEFAULT = COLOR_PURPLE;

const std::vector<SDL_Color> TRANSITION_COLOR_ORDER = {
        COLOR_PURPLE,
        COLOR_GREY,
        COLOR_BLUE,
        COLOR_GREY,
        COLOR_GREEN,
        COLOR_PINK,
        COLOR_GREEN,
        COLOR_GREEN_LIGHT,
        COLOR_SALMON,
        COLOR_GREEN_LIGHT,
        COLOR_PINK_LIGHT,
        COLOR_CYAN,
        COLOR_ORANGE,
        COLOR_BLUE,
        COLOR_YELLOW,
        COLOR_CYAN,
        COLOR_BLUE,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_CYAN,
        COLOR_YELLOW,
        COLOR_BLUE_LIGHT,
        COLOR_GREY,
        COLOR_PURPLE
};

class Map {
public:
    Map();

    void setColor(SDL_Color color){m_Color = color;};
    [[nodiscard]] Node* getNode(wint_t a) const {return m_NodeList[a];};
    [[nodiscard]] unsigned long getNodeCount() const {return m_NodeList.size() - 1;};

    void draw(SDL_Renderer* renderer);

private:
    std::vector<Node*> m_NodeList;
    SDL_Color m_Color;
};

