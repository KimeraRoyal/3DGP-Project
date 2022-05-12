#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include <glm/vec2.hpp>

#include "Settings.h"

#include "Input.h"
#include "Time.h"
#include "Audio.h"

#include "Scene.h"

class Window
{
private:
	//TODO: Don't use a singleton
	static Window* s_instance;

	SDL_Window* m_window;

	Settings m_settings;
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

	Settings* GetSettings() { return &m_settings; }
	Resources* GetResources() { return &m_resources; }

	Input* GetInput() { return &m_input; }
	Time* GetTime() { return &m_time; }
	Audio* GetAudio() { return &m_audio; }

	static Window* GetInstance() { return s_instance; }
};

