#include "../Header/Node.h"
#include "../Header/SDL_overload.h"

Node::Node(Point* start1, Point* end1, Point* start2, Point* end2) {
    m_Inner = new Line(start1, end1);
    m_Outer = new Line(start2, end2);
}

Node::Node() {
    m_Inner = new Line();
    m_Outer = new Line();
}

Node::Node(Line* inner, Line* outer) {
    m_Inner = inner;
    m_Outer = outer;
}

void Node::draw(SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, m_Inner);
    SDL_RenderDrawLine(renderer, m_Outer);
    SDL_RenderDrawLine(renderer, m_Inner->begin.x, m_Inner->begin.y, m_Outer->begin.x, m_Outer->begin.y);
    SDL_RenderDrawLine(renderer, m_Inner->end.x, m_Inner->end.y, m_Outer->end.x, m_Outer->end.y);
}
