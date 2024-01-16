#pragma once

#include "Shapes.h"
#include <vector>
#include <SDL.h>

class Path {
public:
    Path();
    void draw(SDL_Renderer* renderer);
    void rotate(double angle);

private:
    std::vector<Line*> m_pLines;
    Point* m_pCenter;
};

Point* getPathCenter(std::vector<Line*> path);