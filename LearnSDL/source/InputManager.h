#pragma once


#include "SDL.h"

#include "Board.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void ProcessEvents(std::shared_ptr<Board> board);

	inline bool get_running() const { return running_; }
private:
	SDL_Event event_;
	bool running_;
};

