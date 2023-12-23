#pragma once

#include "Shapes.h"
#include <SDL.h>
#include <string>

class Actor {
public:
    Actor() {};
    Actor(int x, int y, int width, int height): m_Position(new Point(x,y)), m_Width(width), m_Height(height){};
    Actor(Point* point, int width, int height): m_Position(point), m_Width(width), m_Height(height){};

    virtual void update() = 0;
    virtual void draw(SDL_Renderer* renderer);

protected:
    Point* m_Position;
    Point* m_MapPosition;
    int m_Width;
    int m_Height;
    std::string m_TextureId;
};