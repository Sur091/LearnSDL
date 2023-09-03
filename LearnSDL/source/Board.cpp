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
	length_(length), width_(width), sep_(sep), snake_tail_({0, 0})
{	
}

Board::~Board()
{
}

void Board::Update()
{
	Automatic();
	HandleEvents();

	// Let Snake play Automatically
	// Snake ate the fruit
	if (IsSnakeEatingFruit())
	{
		// std::cout << "last " << last_.x << ' ' << last_.y << '\n';
		snake_->AddBody(snake_tail_);
		
		GetNewFruit();
	}

	snake_->Log();
	// Update the snake's Position
	snake_tail_ = snake_->get_head();
	snake_->Update(length_, width_);
}

void Board::HandleEvents()
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
}

void Board::Show(SDL_Renderer* renderer, SDL_Window* window)
{
	SDL_SetRenderDrawColor(renderer, 52, 52, 52, 255);
	SDL_RenderClear(renderer);


	fruit_->Show(renderer, sep_);
	snake_->Show(renderer, sep_);
	DrawLines(renderer);

	//opening_->Show(renderer);


	SDL_Delay(Levels[(int)Level::UNDEFINED]);

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

void Board::Automatic()
{
	auto vel = snake_->get_head() - fruit_->get_pos();
	if (vel.real() == 0)
	{
		if (vel.imag() == 0) return;
		if (vel.imag() < 0)
			game_events_.push_front(Events::DOWN);
		else
			game_events_.push_front(Events::UP);
	}
	else
	{
		if (vel.real() < 0)
			game_events_.push_front(Events::RIGHT);
		else
			game_events_.push_front(Events::LEFT);
	}
}

void Board::AddEvent(Events event)
{
	game_events_.push_front(event);
}

bool Board::IsSnakeEatingFruit()
{
	return snake_->IsHeadAt(fruit_->x_, fruit_->y_);
}

bool Board::IsFruitInsideSnake()
{
	return snake_->IsIntersecting(fruit_->x_, fruit_->y_);
}

 void Board::GetNewFruit()
{
	do 
	{
		fruit_->x_ = RandomInt(length_);
		fruit_->y_ = RandomInt(width_);
	} while (IsFruitInsideSnake());
}
