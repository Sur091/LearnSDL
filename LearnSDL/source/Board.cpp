#include "Board.h"

#include <random>
#include <iostream>

std::uint32_t RandomInt(const std::uint32_t max)
{
	static bool is_seeded = false;
	static std::mt19937 generator;

	if (!is_seeded)
	{
		std::random_device rd;
		generator.seed(rd());
		is_seeded = true;
	}

	std::uniform_int_distribution<std::uint32_t> distribution(0, max-1);
	return distribution(generator);
}

Board::Board(const uint32_t length, const uint32_t width, const uint32_t sep) :
	snake_(new Snake()), fruit_(new Fruit(RandomInt(length), RandomInt(width))), game_events_(std::stack<Events>{}),
	length_(length), width_(width), sep_(sep), last_(Box{0, 0})
{	
}

Board::~Board()
{
}

void Board::Update()
{
	// Snake ate the fruit
	if (IsSnakeEatingFruit())
	{
		// std::cout << "last " << last_.x << ' ' << last_.y << '\n';
		snake_->AddBody(last_);
		while (IsFruitInsideSnake())
		{
			fruit_->x_ = RandomInt(length_);
			fruit_->y_ = RandomInt(width_);
		}
	}
	// snake_->Print();
	last_ = snake_->get_last();
	snake_->Update();

	// Process some events
	while (!game_events_.empty())
	{
		Events event = game_events_.top();
		game_events_.pop();

		switch (event)
		{
		case Events::UP:
			snake_->GoUp(); break;
		case Events::DOWN:
			snake_->GoDown(); break;
		case Events::LEFT:
			snake_->GoLeft(); break;
		case Events::RIGHT:
			snake_->GoRight(); break;
			
		}
	}
}

void Board::Show(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
	SDL_RenderClear(renderer);


	fruit_->Show(renderer, sep_);
	snake_->Show(renderer, sep_);

	DrawLines(renderer);
}

void Board::DrawLines(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int x_pos = 0, max_x = length_ * sep_, max_y = width_ * sep_; x_pos < max_x; x_pos += sep_)
	{
		SDL_RenderDrawLine(renderer, x_pos, 0, x_pos, max_y);
	}

	for (int y_pos = 0, max_y = width_ * sep_, max_x = length_ * sep_; y_pos < max_y; y_pos += sep_)
	{
		SDL_RenderDrawLine(renderer, 0, y_pos, max_x, y_pos);
	}
}

void Board::AddEvent(Events event)
{
	game_events_.push(event);
}

bool Board::IsSnakeEatingFruit()
{
	return snake_->HeadAt(fruit_->x_, fruit_->y_);
}

bool Board::IsFruitInsideSnake()
{
	return snake_->IsIntersecting(fruit_->x_, fruit_->y_);
}
