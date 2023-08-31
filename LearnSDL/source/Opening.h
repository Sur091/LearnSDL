#pragma once

#include "SDL.h"

class Opening
{
public:
	Opening(SDL_Window* window, int32_t windowWidth, int32_t windowHeight);
	~Opening();

	void Show(SDL_Renderer* renderer);
	void Update();
private:
	SDL_Surface* main_surface_;
	SDL_Surface* image_;
	SDL_Rect rectangle_;
};

