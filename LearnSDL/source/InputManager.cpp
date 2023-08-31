#include "InputManager.h"

#include "Board.h"

InputManager::InputManager():
	event_(SDL_Event()), running_(true)
{
}

InputManager::~InputManager()
{
}

void InputManager::ProcessEvents(std::shared_ptr<Board> board)
{
	while (SDL_PollEvent(&event_))
	{
		switch (event_.type)
		{
		case SDL_QUIT:
			running_ = false; break;
		case SDL_KEYDOWN:
			switch (event_.key.keysym.sym)
			{
			case SDLK_RIGHT:
				board->AddEvent(Board::Events::RIGHT); break;
			case SDLK_LEFT:
				board->AddEvent(Board::Events::LEFT); break;
			case SDLK_UP:
				board->AddEvent(Board::Events::UP); break;
			case SDLK_DOWN:
				board->AddEvent(Board::Events::DOWN); break;
			}; break;
		default:
			break;
		}
	}
}
