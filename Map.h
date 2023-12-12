#pragma once

#include "Node.h"
#include <SDL.h>
#include <vector>

const int MAX_SEGMENTS = 16;

class Map {
public:
//    Map(Node* nodes[]);
    Map();

    void draw(SDL_Renderer* renderer);

private:
    std::vector<Node*> m_NodeList;
};

