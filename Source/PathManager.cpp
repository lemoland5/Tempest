#include "../Header/PathManager.h"
#include <fstream>
#include <string>

PathManager *PathManager::s_pInstance = nullptr;

PathManager *PathManager::getInstance() {
    if(!s_pInstance) s_pInstance = new PathManager;
    return s_pInstance;
}

const std::string delimiter = ",";

Line* stringToLine(std::string line) {
    int values[4];
    int i = 0;
    std::string token;
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        values[i] = std::stoi(token);
        line.erase(0, pos + delimiter.length());
        i++;
    }
    return new Line(new Point((float)values[0], (float)values[1]), new Point((float)values[2], (float)values[3]));
}

SDL_Color stringToColor(std::string line){
    int values[4];
    int i = 0;
    std::string token;
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        values[i] = std::stoi(token);
        line.erase(0, pos + delimiter.length());
        i++;
    }

    return {static_cast<Uint8>(values[0]), static_cast<Uint8>(values[1]), static_cast<Uint8>(values[2]), static_cast<Uint8>(values[3])};
}

void PathManager::loadPath(const std::string& path, const std::string& id) {
    std::ifstream file;
    std::string line;
    int lineNumber = 0;
    file.open(path);

    auto* res = new std::vector<Line*>;
    SDL_Color color;

    if ( file.is_open() ) {
        while ( file ) {
            std::getline (file, line);

            if(lineNumber == 0){
                color = stringToColor(line);

            }
            else{
                res->push_back(stringToLine(line));
            }
            lineNumber++;
        }
    }

    res->pop_back();
    m_pPaths[id] = new Path(res, color);
}

void PathManager::drawPath(SDL_Renderer* renderer, const std::string& id) {
    m_pPaths[id]->draw(renderer);
}

[[maybe_unused]] void PathManager::movePathX(const std::string& id, float x) {
    m_pPaths[id]->moveX(x);
}

[[maybe_unused]] void PathManager::movePathXAbs(const std::string& id, float x) {
    m_pPaths[id]->moveXAbs(x);
}

void PathManager::movePathY(const std::string& id, float y) {
    m_pPaths[id]->moveY(y);
}
void PathManager::movePathYAbs(const std::string& id, float y) {
    m_pPaths[id]->moveYAbs(y);
}

void PathManager::drawPath(SDL_Renderer *renderer, const std::string& id, int x, int y) {
    m_pPaths[id]->moveXAbs((float)x);
    m_pPaths[id]->moveYAbs((float)y);
    drawPath(renderer, id);
}

void PathManager::drawPath(SDL_Renderer *renderer, const std::string& id, int x, int y, float angle) {
    m_pPaths[id]->rotateAbs(angle);
    drawPath(renderer, id, x, y);
}

void PathManager::drawPath(SDL_Renderer *renderer, const std::string& id, int x, int y, float angle, SDL_Color color) {
    m_pPaths[id]->moveXAbs((float)x);
    m_pPaths[id]->moveYAbs((float)y);
    m_pPaths[id]->rotateAbs(angle);

    m_pPaths[id]->draw(renderer, color);
}
