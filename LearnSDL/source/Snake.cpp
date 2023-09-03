#include "Snake.h"

#include <iostream>

Snake::Snake() :
	body_(std::vector<std::complex<int32_t>>{{ 0, 0 }}),
	velocity_{1, 0}
{
}

Snake::~Snake()
{
}

const std::array<std::complex<int32_t>, 4> Snake::kDirections{
		std::complex<int32_t>{ 0, -1},
		std::complex<int32_t>{ 0,  1},
		std::complex<int32_t>{-1,  0},
		std::complex<int32_t>{ 1,  0},
};

void Snake::Update(int32_t length, int32_t width)
{
	for (auto box = body_.end()-1; box > body_.begin(); box--)
	{
		*box = *(box - 1);
	}

	body_[0] = std::complex<int32_t>{
		(length + body_[0].real() + velocity_.real()) % length,
		(width + body_[0].imag() + velocity_.imag()) % width
	};
}

void Snake::Show(SDL_Renderer* renderer, uint32_t sep)
{
	SDL_SetRenderDrawColor(renderer, 120, 230, 120, 255);
	for (auto box: body_)
	{
		box *= sep;
		const SDL_Rect rectangle{box.real(), box.imag(), sep, sep};
		SDL_RenderFillRect(renderer, &rectangle);
	}
	DrawEyes(renderer, sep);

}

void Snake::DrawEyes(SDL_Renderer* renderer, int32_t sep)
{

	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	const std::complex<int32_t> head = body_[0] * sep;

	const int32_t parts = 8; // How big do you want the eye to be, smaller number = bigger eyes
	sep /= parts;

	if (velocity_ == kDirections[(int)Direction::UP])
	{
		x1 = head.real() + sep,				  y1 = head.imag() + sep;
		x2 = head.real() + (parts - 2) * sep, y2 = head.imag() + sep;
	}
	else if (velocity_ == kDirections[(int)Direction::DOWN])
	{
		x1 = head.real() + sep,				  y1 = head.imag() + (parts - 2) * sep;
		x2 = head.real() + (parts - 2) * sep, y2 = head.imag() + (parts - 2) * sep;
	}
	else if (velocity_ == kDirections[(int)Direction::RIGHT])
	{
		x1 = head.real() + (parts - 2) * sep, y1 = head.imag() + sep;
		x2 = head.real() + (parts - 2) * sep, y2 = head.imag() + (parts - 2) * sep;
	}
	else if (velocity_ == kDirections[(int)Direction::LEFT])
	{
		x1 = head.real() + sep,				  y1 = head.imag() + sep;
		x2 = head.real() + sep,				  y2 = head.imag() + (parts - 2) * sep;
	}
	SDL_Rect eye1 = SDL_Rect{ x1, y1, sep, sep }, eye2 = SDL_Rect{ x2, y2, sep, sep };
	SDL_SetRenderDrawColor(renderer, 230, 120, 120, 255);
	SDL_RenderFillRect(renderer, &eye1);
	SDL_RenderFillRect(renderer, &eye2);
}


bool Snake::IsIntersecting(int32_t x, int32_t y)
{
	for (auto &box: body_)
	{
		if (box.real() == x && box.imag() == y)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsHeadAt(int32_t x, int32_t y)
{
	return body_[0].real() == x && body_[0].imag() == y;
}

void Snake::Log()
{
	std::cout << "Location\n";
	for (auto& box : body_)
	{
		std::cout << box << '\n';
	}
	std::cout << "Velocity " << velocity_ << '\n';
	std::cout << "\n";
}

bool Snake::Go(Direction direction)
{
	if (velocity_ != -kDirections[(int)direction])
	{
		velocity_ = kDirections[(int)direction];
		return true;
	}
	return false;
}
