#pragma once

#include "Shapes.h"
#include <SDL.h>
#include <string>

class Actor {
public:
    Actor() {};
    Actor(int x, int y, int width, int height, std::string id): m_MapPosition(new Point(x,y)), m_Width(width), m_Height(height), m_TextureId(id){};
    Actor(Point* point, int width, int height): m_MapPosition(point), m_Width(width), m_Height(height){};

    virtual void update() = 0;
    virtual void draw(SDL_Renderer* renderer);

    void moveX(int x);
    void moveY(int y);

protected:
    Point* m_Position;
    Point* m_MapPosition;
    float m_Anchor = 0.5f;
    int m_Width;
    int m_Height;
    std::string m_TextureId;
};