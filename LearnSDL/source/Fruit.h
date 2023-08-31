#pragma once

#include <cstdint>

#include "SDL.h"

class Fruit
{
public:
	Fruit(uint32_t limit_x, uint32_t limit_y);

	~Fruit();

	void Show(SDL_Renderer* renderer, uint32_t sep);

	uint32_t x_;
	uint32_t y_;
};