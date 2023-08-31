#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "Game.h"

static const char* kNameOfTheGame = "Rectangle";

int main(int argc, int* argv[])
{

	Game game(kNameOfTheGame);
	game.Run();


	return 0;
}