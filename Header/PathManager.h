#pragma once

#include "Path.h"
#include "Shapes.h"
#include <map>
#include <string>
#include <vector>

class PathManager {
public:
    void loadPath(std::string path, std::string id);

    void drawPath(SDL_Renderer* renderer, std::string id);
    void movePathX(std::string id, double x);
    void movePathXAbs(std::string id, double x);
    void movePathY(std::string id, double y);
    void movePathYAbs(std::string id, double y);

    static PathManager* getInstance();
private:
    static PathManager* s_pInstance;
    PathManager() = default;

    std::map<std::string, Path*> m_pPaths;

};