#pragma once

#include "Node.h"
#include <SDL.h>
#include <vector>

class Map {
public:
//    Map(Node* nodes[]);
    Map();

    void draw(SDL_Renderer* renderer);
    [[nodiscard]] Node* getNode(wint_t a) const {return m_NodeList[a];};

private:
    std::vector<Node*> m_NodeList;
};