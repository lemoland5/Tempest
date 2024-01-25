#pragma once

#include "Shapes.h"
#include "SDL2/SDL.h"


inline int SDL_SetRenderDrawColor(SDL_Renderer* renderer, SDL_Color color){
    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

inline int SDL_RenderDrawLine(SDL_Renderer* renderer, Line* line){
    return SDL_RenderDrawLine(renderer, line->m_pBegin->x, line->m_pBegin->y, line->m_pEnd->x, line->m_pEnd->y);
}

inline int SDL_RenderDrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color);
    return SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
}

inline int SDL_RenderDrawLine(SDL_Renderer* renderer, Line* line, SDL_Color color){
    SDL_SetRenderDrawColor(renderer,color);
    return SDL_RenderDrawLine(renderer, line->m_pBegin->x, line->m_pBegin->y, line->m_pEnd->x, line->m_pEnd->y);
}
