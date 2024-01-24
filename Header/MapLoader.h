#pragma once

#include "Node.h"
#include <iostream>
#include <vector>
#include <string>

class MapLoader {
public:
    static MapLoader* getInstance();
    std::vector<Node*> load(std::string);
private:
    static MapLoader* s_pInstance;
    MapLoader(){};
};