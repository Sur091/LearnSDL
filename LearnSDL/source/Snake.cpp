#include "Snake.h"

#include <iostream>

Snake::Snake() :
	body_(std::vector<Box>{Box{ 0, 0 }}),
	length_(1),
	velocity_{1, 0}
{
}

Snake::~Snake()
{
}

void Snake::Update()
{
	for (int i = body_.size() - 1; i > 0; i--)
	{
		body_[i] = body_[i - 1];
	}
	body_[0].x += velocity_.x;
	body_[0].y += velocity_.y;
}

void Snake::Show(SDL_Renderer* renderer, uint32_t sep)
{
	SDL_SetRenderDrawColor(renderer, 120, 230, 120, 255);
	for (auto &box: body_)
	{
		const SDL_Rect rectangle{box.x * sep, box.y * sep, sep, sep};
		SDL_RenderFillRect(renderer, &rectangle);
	}

}


bool Snake::IsIntersecting(uint32_t x, uint32_t y)
{
	for (auto &box: body_)
	{
		if (box.x == x && box.y == y)
		{
			return true;
		}
	}
	return false;
}

bool Snake::HeadAt(uint32_t x, uint32_t y)
{
	return body_[0].x == x && body_[0].y == y;
}

void Snake::Print()
{
	for (auto& box : body_)
	{
		std::cout << "box: " << box.x << ' ' << box.y << '\n';
	}
	std::cout << "\n";
}
