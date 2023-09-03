#pragma once

#include <memory>
#include <deque>
#include <array>

#include "SDL.h"

#include "Snake.h"
#include "Fruit.h"
#include "Opening.h"


class Board
{
public:
	Board(const uint32_t length, const uint32_t width, const uint32_t sep, SDL_Window* window);
	~Board();

	enum class Events
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
	};
	void Update();
	void HandleEvents();
	void Show(SDL_Renderer* renderer, SDL_Window* window);
	void DrawLines(SDL_Renderer* renderer);
	void Automatic();
	
	void AddEvent(Events event);

	bool IsSnakeEatingFruit();
	bool IsFruitInsideSnake();
	void GetNewFruit();
private:
	std::unique_ptr<Snake> snake_;
	std::unique_ptr<Fruit> fruit_;
	std::unique_ptr<Opening> opening_;

	std::deque<Events> game_events_;

	uint32_t length_, width_, sep_;
	std::complex<int32_t> snake_tail_;

	enum class Level
	{
		ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, UNDEFINED,
	};
	const std::array<int32_t, 12> Levels = { 2500, 500, 333, 250, 200, 166, 143, 125, 111, 100, 91, 0};
};

