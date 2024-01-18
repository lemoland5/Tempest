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

    std::cout<<m_Color.g<<"\n";
}


void Path::draw(SDL_Renderer* renderer) {
//    std::cout<<"drawing \n";
    for(auto & line : *m_pLines){
        // std::cout<<line->getLength()<<"\n";
        SDL_RenderDrawLine(renderer, line);
        SDL_RenderDrawLine(renderer, new Line(m_pCenter, line->m_pBegin), m_Color);
        SDL_RenderDrawLine(renderer, new Line(m_pCenter, line->m_pEnd), m_Color);
    }
}

void Path::rotate(float angle) {
    // std::cout<<"CENTER: "<<m_pCenter->x<<", "<<m_pCenter->y<<"\n";


    for(auto & line : *m_pLines){
        line->m_pBegin = rotatePoint(m_pCenter, line->m_pBegin, angle);
        line->m_pEnd = rotatePoint(m_pCenter, line->m_pEnd, angle);
    }

    m_Rotation += angle;
}

void Path::moveX(float x) {
    for(auto & line : *m_pLines){
        line->m_pBegin->x += x;
        line->m_pEnd->x += x;
    }
    m_pCenter = getPathCenter(m_pLines);
}

void Path::moveY(float y) {
    for(auto & line : *m_pLines){
        line->m_pBegin->y += y;
        line->m_pEnd->y += y;
    }
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

    for(auto & line : (*path)){
        if(line->m_pBegin->x < minX){
            minX = line->m_pBegin->x;
        }
        if(line->m_pEnd->x < minX){
            minX = line->m_pEnd->x;
        }
        if(line->m_pBegin->x > maxX){
            maxX = line->m_pBegin->x;
        }
        if(line->m_pEnd->x > maxX){
            maxX = line->m_pEnd->x;
        }

        if(line->m_pBegin->y < minY){
            minY = line->m_pBegin->y;
        }
        if(line->m_pEnd->y < minY){
            minY = line->m_pEnd->y;
        }
        if(line->m_pBegin->y > maxY){
            maxY = line->m_pBegin->y;
        }
        if(line->m_pEnd->y > maxY){
            maxY = line->m_pEnd->y;
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