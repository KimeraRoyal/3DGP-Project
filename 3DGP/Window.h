#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include <glm/vec2.hpp>

#include "Triangle.h"

class Window
{
private:
	static constexpr glm::ivec2 c_defaultWindowSize = glm::ivec2(240, 160);
	static constexpr int c_defaultWindowScale = 4;

	SDL_Window* m_window;

	std::unique_ptr<Triangle> m_triangle;

	bool PollEvents();
	bool Update();
	void Draw();
public:
	Window();
	~Window();

	void GameLoop();
};

