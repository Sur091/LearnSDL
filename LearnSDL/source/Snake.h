#pragma once

#include <cstdint>
#include <vector>

#include "SDL.h"

struct Box
{
	uint32_t x;
	uint32_t y;
};


class Snake
{
public:
	Snake();
	~Snake();
		
	void Update();
	void Show(SDL_Renderer* renderer, uint32_t sep);

	void AddBody(Box tail) { body_.push_back(tail); };

	bool IsIntersecting(uint32_t x, uint32_t y);
	bool HeadAt(uint32_t x, uint32_t y);
	void Print();

	inline Box get_last() const { return body_[body_.size() - 1]; }

	inline void GoUp() { if (velocity_.y == 0) { velocity_.x = 0; velocity_.y = -1; } }
	inline void GoDown() { if (velocity_.y == 0) { velocity_.x = 0; velocity_.y = 1; } }
	inline void GoLeft() { if (velocity_.x == 0) { velocity_.x = -1; velocity_.y = 0; } }
	inline void GoRight() { if (velocity_.x == 0) { velocity_.x = 1; velocity_.y = 0; } }
private:

	std::vector<Box> body_;
	uint32_t length_;
	Box velocity_;

};

