#pragma once

#include "Shapes.h"
#include <vector>

class PathLoader {
public:
    std::vector<Line*> loadPath(std::string path);

    static PathLoader* getInstance();
private:
    static PathLoader* s_pInstance;
    PathLoader() = default;
};