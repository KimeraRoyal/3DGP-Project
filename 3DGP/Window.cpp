#include "Window.h"

#include <stdexcept>

#include <GL/glew.h>
#include <iostream>

#include "SettingsParser.h"
#include "KeybindParser.h"
#include "SceneParser.h"

Window* Window::s_instance = nullptr;

Window::Window()
{
	s_instance = this;
	
	const SettingsParser settingsParser = SettingsParser();
	settingsParser.Parse("data/settings.json", m_settings);

	m_moveWindow = true;
	m_windowAnchor = glm::vec2(0.5f);
	m_windowPosition = glm::vec2(0.0f, 0.0f);

	m_resolution = m_settings.GetScreenResolution();
	m_scale = m_settings.GetScreenScale();

	m_window = SDL_CreateWindow("3D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GetScaledResolution().x, GetScaledResolution().y, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glHint(GL_SAMPLES, m_settings.GetMultisampleCount());

	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
	{
		throw std::runtime_error("Failed to create SDL GL context.");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize OpenGL.");
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	m_screenSize = glm::ivec2(displayMode.w, displayMode.h);
	
	const KeybindParser keybindParser = KeybindParser();
	keybindParser.Parse("data/bindings.json", m_input);

	m_audio.LoadBank("data/banks/Desktop/Master.bank");
	m_audio.LoadBank("data/banks/Desktop/Master.strings.bank");
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::GameLoop()
{
	while (PollEvents() && Update())
	{
		Draw();
	}
}

void Window::Start()
{
	SceneParser sceneParser(&m_settings, &m_resources);
	m_scene = sceneParser.Parse("data/scenes/test_scene.json");

	m_scene->Start();
}

bool Window::PollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			return false;
			
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			m_input.RegisterKeyboardInput(&e);
			break;
			
		default:
			break;
		}
	}

	return true;
}

bool Window::Update()
{
	m_time.Update();
	m_scene->Update(m_time, m_input);
	m_audio.Update();
	
	m_input.PostUpdate();

	return true;
}

void Window::Draw()
{
	if(m_moveWindow)
	{
		const glm::vec2 windowPos = glm::uvec2(glm::vec2(m_screenSize - GetScaledResolution()) * m_windowAnchor + m_windowPosition);
		SDL_SetWindowPosition(m_window, static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
	}
	
	SDL_GL_MakeCurrent(m_window, m_context);
	m_scene->Draw();

	SDL_GL_SwapWindow(m_window);
}