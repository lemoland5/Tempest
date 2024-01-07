#pragma once

#include "Node.h"
#include <SDL.h>
#include <vector>

class Map {
public:
//    Map(Node* nodes[]);
    Map();

    [[nodiscard]] Node* getNode(wint_t a) const {return m_NodeList[a];};
    [[nodiscard]] unsigned long getNodeCount() const {return m_NodeList.size() - 1;};


    void draw(SDL_Renderer* renderer);


private:
    std::vector<Node*> m_NodeList;
};