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

Board::Board(const uint32_t length, const uint32_t width, const uint32_t sep, SDL_Window* window) :
	snake_(new Snake()), 
	fruit_(new Fruit(RandomInt(length), RandomInt(width))), 
	opening_(new Opening(window, length*sep, width*sep)),
	game_events_(std::deque<Events>{}),
	length_(length), width_(width), sep_(sep), last_({0, 0})
{	
}

Board::~Board()
{
}

void Board::Update()
{
	bool changed_directions = false;
	// Process some events
	while (!changed_directions && !game_events_.empty())
	{
		changed_directions = false;
		Events event = game_events_.back();
		game_events_.pop_back();

		switch (event)
		{
		case Events::UP:
			changed_directions = snake_->Go(Snake::Direction::UP); break;
		case Events::DOWN:
			changed_directions = snake_->Go(Snake::Direction::DOWN); break;
		case Events::LEFT:
			changed_directions = snake_->Go(Snake::Direction::LEFT); break;
		case Events::RIGHT:
			changed_directions = snake_->Go(Snake::Direction::RIGHT); break;
		}
	}
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

	// Update the snake's Position
	snake_->Print();
	last_ = snake_->get_last();
	snake_->Update();
}

void Board::Show(SDL_Renderer* renderer, SDL_Window* window)
{
	//SDL_RenderClear(renderer);


	//fruit_->Show(renderer, sep_);
	//snake_->Show(renderer, sep_);
	opening_->Show(renderer);

	//DrawLines(renderer);

	SDL_Delay(Levels[(int)Level::EIGHT]);

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
	game_events_.push_front(event);
}

bool Board::IsSnakeEatingFruit()
{
	return snake_->HeadAt(fruit_->x_, fruit_->y_);
}

bool Board::IsFruitInsideSnake()
{
	return snake_->IsIntersecting(fruit_->x_, fruit_->y_);
}
