#pragma once

#include "Path.h"
#include "Shapes.h"
#include <map>
#include <string>
#include <vector>

class PathManager {
public:
    void loadPath(const std::string& path, const std::string& id);

    void drawPath(SDL_Renderer* renderer, std::string id);
    void drawPath(SDL_Renderer* renderer, std::string id, int x, int y);
    void drawPath(SDL_Renderer* renderer, std::string id, int x, int y, float angle);
    void drawPath(SDL_Renderer* renderer, std::string id, int x, int y, float angle, SDL_Color color);

    void movePathX(std::string id, float x);
    void movePathXAbs(std::string id, float x);
    void movePathY(std::string id, float y);
    void movePathYAbs(std::string id, float y);

//     TODO: MOVE TO PRIVATE
//    std::map<std::string, Path*> m_pPaths;

    void destroy(){m_pPaths.clear();};

    static PathManager* getInstance();
private:
    static PathManager* s_pInstance;
    PathManager() = default;

    std::map<std::string, Path*> m_pPaths;

};