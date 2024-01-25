#include "../Header/Path.h"
#include "../Header/PathManager.h"
#include "../Header/SDL_overload.h"
#include <iostream>

Path::Path() {
//    m_pLines = PathManager::getInstance()->loadPath("../Assets/player.path");
    m_pCenter = getPathCenter(m_pLines);
    // std::cout<<m_pCenter->x<<" - "<<m_pCenter->y<<"\n";


}

Path::Path(std::vector<Line *>* lines): Path(lines, {255,255,255,255}) {};


Path::Path(std::vector<Line *>* lines, SDL_Color color) {
    m_pLines = lines;
    m_Color = color;
    m_pCenter = getPathCenter(m_pLines);

//    std::cout<<m_Color.g<<"\n";
}


void Path::draw(SDL_Renderer* renderer) {
    draw(renderer, m_Color);
}

void Path::draw(SDL_Renderer *renderer, SDL_Color color) {
    for(int i = 0; i < m_pLines->size(); i++){
        // std::cout<<line->getLength()<<"\n";
        SDL_RenderDrawLine(renderer, (*m_pLines)[i], color);
//        SDL_RenderDrawLine(renderer, new Line(m_pCenter, line->m_pBegin), m_Color);
//        SDL_RenderDrawLine(renderer, new Line(m_pCenter, line->m_pEnd), m_Color);
    }
}

void Path::rotate(float angle) {
    // std::cout<<"CENTER: "<<m_pCenter->x<<", "<<m_pCenter->y<<"\n";


    for(int i = 0; i < m_pLines->size(); i++){
        (*m_pLines)[i]->m_pBegin = rotatePoint(m_pCenter, (*m_pLines)[i]->m_pBegin, angle);
        (*m_pLines)[i]->m_pEnd = rotatePoint(m_pCenter, (*m_pLines)[i]->m_pEnd, angle);
    }

    m_Rotation += angle;
}

void Path::moveX(float x) {
    for(int i = 0; i < m_pLines->size(); i++){
        (*m_pLines)[i]->m_pBegin->x += x;
        (*m_pLines)[i]->m_pEnd->x += x;
    }
    delete m_pCenter;
    m_pCenter = getPathCenter(m_pLines);
}

void Path::moveY(float y) {
    for(int i = 0; i < m_pLines->size(); i++){
        (*m_pLines)[i]->m_pBegin->y += y;
        (*m_pLines)[i]->m_pEnd->y += y;
    }
    delete m_pCenter;

    m_pCenter = getPathCenter(m_pLines);

}

void Path::moveXAbs(float x) {
    float difference = x - m_pCenter->x;

    moveX(difference);
}

void Path::moveYAbs(float y) {
    float difference = y - m_pCenter->y;
    moveY(difference);
}

void Path::rotateAbs(float angle) {
    float difference = angle - m_Rotation;
    rotate(difference);
}




Point* getPathCenter(std::vector<Line*>* path){
//    std::cout<<path.size()<<"\n";

//    for(auto & line : path){
//        std::cout<<line->m_pBegin->x<<", "<<line->m_pBegin->y<<"; "<<line->m_pEnd->x<<" "<<line->m_pEnd->y<<"\n";
//    }

    float centerX;
    float centerY;

    int minX = (*path)[0]->m_pBegin->x;
    int maxX = minX;
    int minY = (*path)[0]->m_pBegin->y;
    int maxY = (*path)[0]->m_pBegin->y;

    for(int i = 0; i < path->size(); i++){
        if((*path)[i]->m_pBegin->x < minX){
            minX = (*path)[i]->m_pBegin->x;
        }
        if((*path)[i]->m_pEnd->x < minX){
            minX = (*path)[i]->m_pEnd->x;
        }
        if((*path)[i]->m_pBegin->x > maxX){
            maxX = (*path)[i]->m_pBegin->x;
        }
        if((*path)[i]->m_pEnd->x > maxX){
            maxX = (*path)[i]->m_pEnd->x;
        }

        if((*path)[i]->m_pBegin->y < minY){
            minY = (*path)[i]->m_pBegin->y;
        }
        if((*path)[i]->m_pEnd->y < minY){
            minY = (*path)[i]->m_pEnd->y;
        }
        if((*path)[i]->m_pBegin->y > maxY){
            maxY = (*path)[i]->m_pBegin->y;
        }
        if((*path)[i]->m_pEnd->y > maxY){
            maxY = (*path)[i]->m_pEnd->y;
        }
    }

    centerX = ((float)minX + (float)maxX) / 2;
    centerY = ((float)minY + (float)maxY) / 2;
//
    // std::cout<<minX<<" - "<<maxX<<"\n";
    // std::cout<<minY<<" - "<<maxY<<"\n";
    // std::cout<<centerX<<" - "<<centerY<<"\n";

    return new Point((int)centerX, (int)centerY);

}