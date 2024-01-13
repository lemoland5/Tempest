#include "../Header/Node.h"
#include "../Header/SDL_overload.h"

Node::Node(Point* start1, Point* end1, Point* start2, Point* end2) {
    m_Inner = new Line(start1, end1);
    m_Outer = new Line(start2, end2);
    m_Axis = new Line(m_Inner->calculateTValuePoint(0.5f), m_Outer->calculateTValuePoint(0.5f));
}

Node::Node() {
    m_Inner = new Line();
    m_Outer = new Line();
    m_Axis = new Line(m_Inner->calculateTValuePoint(0.5f), m_Outer->calculateTValuePoint(0.5f));

}

Node::Node(Line* inner, Line* outer) {
    m_Inner = inner;
    m_Outer = outer;
    m_Axis = new Line(m_Inner->calculateTValuePoint(0.5f), m_Outer->calculateTValuePoint(0.5f));

}

void Node::draw(SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, m_Inner);
    SDL_RenderDrawLine(renderer, m_Outer);
    SDL_RenderDrawLine(renderer, m_Inner->m_pBegin->x, m_Inner->m_pBegin->y, m_Outer->m_pBegin->x, m_Outer->m_pBegin->y);
    SDL_RenderDrawLine(renderer, m_Inner->m_pEnd->x, m_Inner->m_pEnd->y, m_Outer->m_pEnd->x, m_Outer->m_pEnd->y);
    SDL_RenderDrawLine(renderer, m_Axis);
}