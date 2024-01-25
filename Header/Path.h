#pragma once

#include "Shapes.h"
#include <vector>
#include <SDL.h>

class Path {
public:
    Path();
    explicit Path(std::vector<Line*>* lines);
    Path(std::vector<Line*>* lines, SDL_Color color);

    void draw(SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer, SDL_Color color);
    void moveX(float x);
    void moveY(float y);
    void moveXAbs(float x);
    void moveYAbs(float x);
    void rotate(float angle);
    void rotateAbs(float angle);

private:
    std::vector<Line*>* m_pLines;
    Point* m_pCenter;
    float m_Rotation = 0;
    SDL_Color m_Color;
};

Point* getPathCenter(std::vector<Line*>* path);