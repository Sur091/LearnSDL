#pragma once

#include <memory>
#include <stack>

#include "SDL.h"


#include "Snake.h"
#include "Fruit.h"




class Board
{
public:
	Board(const uint32_t length, const uint32_t width, const uint32_t sep);
	~Board();

	enum class Events
	{
		UP = 0,
		LEFT,
		RIGHT,
		DOWN,
	};
	void Update();
	void Show(SDL_Renderer* renderer);
	void DrawLines(SDL_Renderer* renderer);
	
	void AddEvent(Events event);

	bool IsSnakeEatingFruit();
	bool IsFruitInsideSnake();
private:
	std::unique_ptr<Fruit> fruit_;
	std::unique_ptr<Snake> snake_;

	std::stack<Events> game_events_;

	uint32_t length_, width_, sep_;
	Box last_;

};

