#include "Opening.h"

Opening::Opening(SDL_Window* window, int32_t windowWidth, int32_t windowHeight):
	main_surface_(SDL_GetWindowSurface(window)),
	image_(SDL_LoadBMP("dependencies/vendor/Snake.bmp")),
	rectangle_(SDL_Rect{ 0, 0, windowWidth, windowHeight })
{
}

Opening::~Opening()
{
}

void Opening::Show(SDL_Renderer* renderer)
{
	SDL_BlitScaled(image_, NULL, main_surface_, &rectangle_);
}

void Opening::Update()
{
}
