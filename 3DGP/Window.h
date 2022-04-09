#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include <glm/vec2.hpp>

#include "Audio.h"
#include "Input.h"
#include "Time.h"
#include "Scene.h"

class Window
{
private:
	static constexpr glm::ivec2 c_defaultWindowSize = glm::ivec2(240, 160);
	static constexpr int c_defaultWindowScale = 6;

	SDL_Window* m_window;

	Resources m_resources;

	Input m_input;
	Time m_time;
	Audio m_audio;

	std::shared_ptr<Scene> m_scene;

	bool PollEvents();
	bool Update();
	void Draw();
public:
	Window();
	~Window();

	void Start();
	void GameLoop();

	static glm::ivec2 GetWindowSize();
	static int GetWindowScale();
	static glm::ivec2 GetScaledWindowSize();
};

