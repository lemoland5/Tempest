#pragma once

#include "Shapes.h"
#include <vector>
#include <SDL.h>

class Path {
public:
    Path();
    Path(std::vector<Line*> lines);

    void draw(SDL_Renderer* renderer);
    void moveX(double x);
    void moveY(double y);
    void rotate(double angle);
    void moveXAbs(double x);
    void moveYAbs(double x);

private:
    std::vector<Line*> m_pLines;
    Point* m_pCenter;
};

Point* getPathCenter(std::vector<Line*> path);