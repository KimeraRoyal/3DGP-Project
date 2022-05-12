#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include "Settings.h"
#include "Resources.h"

#include "Input.h"
#include "Time.h"
#include "Audio.h"

#include "Scene.h"

class Window
{
private:
	//TODO: Don't use a singleton
	static Window* s_instance;

	glm::uvec2 m_screenSize;

	bool m_moveWindow;
	glm::vec2 m_windowAnchor;
	glm::vec2 m_windowPosition;
	
	glm::uvec2 m_resolution;
	unsigned int m_scale;

	SDL_Window* m_window;
	SDL_GLContext m_context;

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

	[[nodiscard]] glm::uvec2 GetScreenSize() const { return m_screenSize; }

	[[nodiscard]] bool GetCanMoveWindow() const { return m_moveWindow; }
	[[nodiscard]] glm::vec2 GetWindowAnchor() const { return m_windowAnchor; }
	[[nodiscard]] glm::vec2 GetWindowPosition() const { return m_windowPosition; }

	[[nodiscard]] glm::uvec2 GetResolution() const { return m_resolution; }
	[[nodiscard]] glm::uvec2 GetScaledResolution() const { return m_resolution * m_scale; }
	[[nodiscard]] unsigned int GetScale() const { return m_scale; }
	
	Settings* GetSettings() { return &m_settings; }
	Resources* GetResources() { return &m_resources; }

	Input* GetInput() { return &m_input; }
	Time* GetTime() { return &m_time; }
	Audio* GetAudio() { return &m_audio; }

	void SetCanMoveWindow(const bool _moveWindow) { m_moveWindow = _moveWindow; }
	void SetWindowAnchor(const glm::vec2 _anchor) { m_windowAnchor = _anchor; }
	void SetWindowPosition(const glm::vec2 _position) { m_windowPosition = _position; }

	static Window* GetInstance() { return s_instance; }
};

