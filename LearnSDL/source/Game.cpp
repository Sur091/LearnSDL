#include "Game.h"

#include <iostream>

#include "InputManager.h"

Game::Game(const char* title) :
	window_(nullptr), renderer_(nullptr), input_manager_(new InputManager()), board_(new Board(kScreenWidth / kSep, kScreenHeight / kSep, kSep)),
	title_(title)
{
	window_ = SDL_CreateWindow(title_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
	if (!window_)
	{
		std::cout << "Failed to create SDL window\n";
		std::cout << SDL_GetError() << '\n';
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer_ = SDL_CreateRenderer(window_, -1, 0);
	if (!renderer_)
	{
		std::cout << "Failed to create SDL renderer\n";
		std::cout << SDL_GetError() << '\n';
		exit(1);
	}


}

Game::~Game()
{
	SDL_Quit();
}

void Game::Run()
{
	while (input_manager_->get_running())
	{
		input_manager_->ProcessEvents(board_);
		
		Update();

		Render();

		SDL_Delay(250);
	}
}

void Game::Update()
{
	board_->Update();
}

void Game::Render()
{
	board_->Show(renderer_);


	SDL_RenderPresent(renderer_);
}
