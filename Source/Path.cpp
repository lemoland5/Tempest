#include "../Header/Path.h"
#include "../Header/PathManager.h"
#include "../Header/SDL_overload.h"

Path::Path() {
    m_pCenter = getPathCenter(m_pLines);
}

Path::Path(std::vector<Line *>* lines): Path(lines, {255,255,255,255}) {};


Path::Path(std::vector<Line *>* lines, SDL_Color color) {
    m_pLines = lines;
    m_Color = color;
    m_pCenter = getPathCenter(m_pLines);


}


void Path::draw(SDL_Renderer* renderer) {
    draw(renderer, m_Color);
}

void Path::draw(SDL_Renderer *renderer, SDL_Color color) {
    for(int i = 0; i < m_pLines->size(); i++){

        SDL_RenderDrawLine(renderer, (*m_pLines)[i], color);


    }
}

void Path::rotate(float angle) {



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






    float centerX;
    float centerY;

    int minX = (int)(*path)[0]->m_pBegin->x;
    int maxX = minX;
    int minY = (int)(*path)[0]->m_pBegin->y;
    int maxY = (int)(*path)[0]->m_pBegin->y;

    for(int i = 0; i < path->size(); i++){
        if((*path)[i]->m_pBegin->x < (float)minX){
            minX = (int)(*path)[i]->m_pBegin->x;
        }
        if((*path)[i]->m_pEnd->x < (float)minX){
            minX = (int)(*path)[i]->m_pEnd->x;
        }
        if((*path)[i]->m_pBegin->x > (float)maxX){
            maxX = (int)(*path)[i]->m_pBegin->x;
        }
        if((*path)[i]->m_pEnd->x > (float)maxX){
            maxX = (int)(*path)[i]->m_pEnd->x;
        }

        if((*path)[i]->m_pBegin->y < (float)minY){
            minY = (int)(*path)[i]->m_pBegin->y;
        }
        if((*path)[i]->m_pEnd->y < (float)minY){
            minY = (int)(*path)[i]->m_pEnd->y;
        }
        if((*path)[i]->m_pBegin->y > (float)maxY){
            maxY = (int)(*path)[i]->m_pBegin->y;
        }
        if((*path)[i]->m_pEnd->y > (float)maxY){
            maxY = (int)(*path)[i]->m_pEnd->y;
        }
    }

    centerX = ((float)minX + (float)maxX) / 2;
    centerY = ((float)minY + (float)maxY) / 2;





    return new Point((float)centerX, (float)centerY);

}