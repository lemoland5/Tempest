<<<<<<< HEAD
#pragma once

#include "Node.h"
#include <SDL.h>
#include <vector>

class Map {
public:
//    Map(Node* nodes[]);
    Map();

    void draw(SDL_Renderer* renderer);

private:
    std::vector<Node*> m_NodeList;
};
=======
#pragma once

#include "MapLoader.h"
#include "Node.h"
#include "SDL2/SDL.h"
#include <vector>

class Map {
public:
//    Map(Node* nodes[]);
    Map();

    void draw(SDL_Renderer* renderer);

private:
    std::vector<Node*> m_NodeList;
};

>>>>>>> 4217a4db963331001f174237192ad3a723382fe7
