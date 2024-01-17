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
    return new Line(new Point(values[0], values[1]), new Point(values[2], values[3]));
}

void PathManager::loadPath(std::string path, std::string id) {
    std::ifstream file;
    std::string line;
    file.open(path);

    std::vector<Line *> res;

    if ( file.is_open() ) {
        while ( file ) {
            std::getline (file, line);
            res.push_back(stringToLine(line));
        }
    }

    res.pop_back();
    m_pPaths[id] = new Path(res);
}

void PathManager::drawPath(SDL_Renderer* renderer, std::string id) {
    m_pPaths[id]->draw(renderer);
}

void PathManager::movePathX(std::string id, double x) {
    m_pPaths[id]->moveX(x);
}

void PathManager::movePathXAbs(std::string id, double x) {
    m_pPaths[id]->moveXAbs(x);
}

void PathManager::movePathY(std::string id, double y) {
    m_pPaths[id]->moveY(y);
}
void PathManager::movePathYAbs(std::string id, double y) {
    m_pPaths[id]->moveYAbs(y);
}