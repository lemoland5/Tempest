#pragma once

#include "Shapes.h"
#include <map>
#include <string>
#include <vector>

class PathManager {
public:
    std::vector<Line*> loadPath(std::string path);

    static PathManager* getInstance();
private:
    static PathManager* s_pInstance;
    PathManager() = default;

    std::map<std::string, std::vector<Line*>> m_pPaths;

};