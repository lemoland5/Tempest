#pragma once

#include "Shapes.h"
#include "SDL2/SDL.h"

class Node {
public:
    Node(Point* start1, Point* end1, Point* start2, Point* end2);
    Node(Line* inner, Line* outer);
    Node();
    ~Node();

    [[nodiscard]] Line* getAxis() const {return m_Axis;};

    void draw(SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer, SDL_Color color);

private:
    Line* m_Inner;
    Line* m_Outer;
    Line* m_Axis;

};