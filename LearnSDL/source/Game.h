#pragma once

#include <memory>
#include <cstdint>

#include "SDL.h"

#include "InputManager.h"
#include "Board.h"

#define SEPERATION 40
#define SCREEN_WIDHT 640
#define SCREEN_HEIGHT 360


class Game
{
public:
	Game(const char *title);
	~Game();

	void Run();

	void Update();

	void Render();

	inline uint32_t get_screen_width() const { return kScreenWidth; }
	inline uint32_t get_screen_height() const { return kScreenHeight; }
	inline const char* get_title() const { return title_; }
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	std::unique_ptr<InputManager> input_manager_;
	std::shared_ptr<Board> board_;

	const char *title_;
	static const uint32_t kScreenWidth = SCREEN_WIDHT;
	static const uint32_t kScreenHeight = SCREEN_HEIGHT;
	static const uint32_t kSep = SEPERATION;

};

