#pragma once

#include "Node.h"
#include <SDL.h>
#include <vector>

const SDL_Color COLOR_MAP_PURPLE = {0, 9, 155, 255};

class Map {
public:
//    Map(Node* nodes[]);
    Map();

    [[nodiscard]] Node* getNode(wint_t a) const {return m_NodeList[a];};
    [[nodiscard]] unsigned long getNodeCount() const {return m_NodeList.size() - 1;};


    void draw(SDL_Renderer* renderer);


private:
    std::vector<Node*> m_NodeList;
    SDL_Color m_Color;
};

