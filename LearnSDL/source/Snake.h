#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <complex>

#include "SDL.h"

struct Box
{
	int32_t x;
	int32_t y;
};


class Snake
{
public:
	Snake();
	~Snake();
		
	void Update();
	void Show(SDL_Renderer* renderer, uint32_t sep);
	void DrawEyes(SDL_Renderer* renderer, int32_t sep);

	void AddBody(const std::complex<int32_t> tail) { body_.push_back(tail); };

	bool IsIntersecting(int32_t x, int32_t y);
	bool HeadAt(int32_t x, int32_t y);
	void Print();

	enum class Direction
	{
		UP = 0, DOWN, LEFT, RIGHT,
	};
	bool Go(Direction direction);

	inline std::complex<int32_t> get_last() const { return body_[body_.size() - 1]; }
private:
	std::vector<std::complex<int32_t>> body_;
	uint32_t length_;
	std::complex<int32_t> velocity_;

private:
	static const std::array<std::complex<int32_t>, 4> kDirections;
};
