#pragma once

#include <complex>
#include <cstdint>

#include "SDL.h"

class Fruit
{
public:
	Fruit(int32_t limit_x, int32_t limit_y);

	~Fruit();

	void Show(SDL_Renderer* renderer, int32_t sep);

	inline std::complex<int32_t> get_pos() { return std::complex<int32_t>{x_, y_}; }

	int32_t x_;
	int32_t y_;
};