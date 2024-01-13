#pragma once

#include "Shapes.h"
#include "SDL2/SDL.h"

inline int SDL_RenderDrawLine(SDL_Renderer* renderer, Line* line){
    return SDL_RenderDrawLine(renderer, line->m_pBegin->x, line->m_pBegin->y, line->m_pEnd->x, line->m_pEnd->y);
}
