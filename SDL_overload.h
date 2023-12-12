#pragma once

#include "Shapes.h"
#include <SDL.h>

inline int SDL_RenderDrawLine(SDL_Renderer* renderer, Line* line){
    return SDL_RenderDrawLine(renderer, line->begin.x, line->begin.y, line->end.x, line->end.y);
}
