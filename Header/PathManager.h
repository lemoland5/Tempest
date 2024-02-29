#pragma once

#include "Path.h"
#include "Shapes.h"
#include <map>
#include <string>
#include <vector>

class PathManager {
public:
    void loadPath(const std::string& path, const std::string& id);

    void drawPath(SDL_Renderer* renderer, const std::string& id);
    void drawPath(SDL_Renderer* renderer, const std::string& id, int x, int y);
    void drawPath(SDL_Renderer* renderer, const std::string& id, int x, int y, float angle);
    void drawPath(SDL_Renderer* renderer, const std::string& id, int x, int y, float angle, SDL_Color color);

    [[maybe_unused]] void movePathX(const std::string& id, float x);
    [[maybe_unused]] void movePathXAbs(const std::string& id, float x);
    [[maybe_unused]] void movePathY(const std::string& id, float y);
    [[maybe_unused]] void movePathYAbs(const std::string& id, float y);




    void destroy(){m_pPaths.clear();};

    static PathManager* getInstance();
private:
    static PathManager* s_pInstance;
    PathManager() = default;

    std::map<std::string, Path*> m_pPaths;

};