#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include <glm/vec2.hpp>

#include "Time.h"
#include "Curuthers.h"

class Window
{
private:
	static constexpr glm::ivec2 c_defaultWindowSize = glm::ivec2(240, 160);
	static constexpr int c_defaultWindowScale = 4;

	SDL_Window* m_window;

	std::unique_ptr<Time> m_time;

	std::unique_ptr<Curuthers> m_triangle;

	bool PollEvents();
	bool Update();
	void Draw();
public:
	Window();
	~Window();

	void GameLoop();

	static glm::ivec2 GetWindowSize();
	static int GetWindowScale();
	static glm::ivec2 GetScaledWindowSize();
};

