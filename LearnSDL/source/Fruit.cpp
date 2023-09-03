#include "Fruit.h"


Fruit::Fruit(int32_t x, int32_t y):
    x_(x),
    y_(y) 
{
}

Fruit::~Fruit()
{
}

void Fruit::Show(SDL_Renderer* renderer, int32_t sep)
{
    SDL_SetRenderDrawColor(renderer, 230, 120, 120, 255);
    const SDL_Rect rectangle{ x_ * sep, y_ * sep, sep, sep };
    SDL_RenderFillRect(renderer, &rectangle);
}
