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
		
	void Update(int32_t length, int32_t width);
	void Show(SDL_Renderer* renderer, uint32_t sep);
	void DrawEyes(SDL_Renderer* renderer, int32_t sep);

	void AddBody(const std::complex<int32_t> tail) { body_.push_back(tail); };

	bool IsIntersecting(int32_t x, int32_t y);
	bool IsHeadAt(int32_t x, int32_t y);
	void Log();


	enum class Direction
	{
		UP = 0, DOWN, LEFT, RIGHT,
	};
	bool Go(Direction direction);

	inline std::complex<int32_t> get_head() { return body_[0]; }
	inline std::complex<int32_t> get_tail() const { return body_[body_.size() - 1]; }
private:
	std::vector<std::complex<int32_t>> body_;
	std::complex<int32_t> velocity_;

private:
	static const std::array<std::complex<int32_t>, 4> kDirections;
};
