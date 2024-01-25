#include "../Header/PathManager.h"
#include <fstream>
#include <iostream>
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
//    std::cout<<values[0]<<", "<<values[1]<<", "<<values[2]<<", "<<values[3]<<"\n";
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
//            std::cout<<lineNumber<<"\n";
            if(lineNumber == 0){
                color = stringToColor(line);
//                std::cout<<color.g<<"\n";
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

void PathManager::drawPath(SDL_Renderer* renderer, std::string id) {
    m_pPaths[id]->draw(renderer);
}

void PathManager::movePathX(std::string id, float x) {
    m_pPaths[id]->moveX(x);
}

void PathManager::movePathXAbs(std::string id, float x) {
    m_pPaths[id]->moveXAbs(x);
}

void PathManager::movePathY(std::string id, float y) {
    m_pPaths[id]->moveY(y);
}
void PathManager::movePathYAbs(std::string id, float y) {
    m_pPaths[id]->moveYAbs(y);
}

void PathManager::drawPath(SDL_Renderer *renderer, std::string id, int x, int y) {
    m_pPaths[id]->moveXAbs(x);
    m_pPaths[id]->moveYAbs(y);
    drawPath(renderer, id);
}

void PathManager::drawPath(SDL_Renderer *renderer, std::string id, int x, int y, float angle) {
    m_pPaths[id]->rotateAbs(angle);
    drawPath(renderer, id, x, y);
}

void PathManager::drawPath(SDL_Renderer *renderer, std::string id, int x, int y, float angle, SDL_Color color) {
    m_pPaths[id]->moveXAbs(x);
    m_pPaths[id]->moveYAbs(y);
    m_pPaths[id]->rotateAbs(angle);

    m_pPaths[id]->draw(renderer, color);
}
