#include "Window.h"

#include <stdexcept>

#include <GL/glew.h>
#include <iostream>

#include "SettingsParser.h"
#include "KeybindParser.h"
#include "SceneParser.h"

Window::Window()
{
	const SettingsParser settingsParser = SettingsParser();
	settingsParser.Parse("data/settings.json", m_settings);

	m_window = SDL_CreateWindow("3D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_settings.GetScaledScreenResolution().x, m_settings.GetScaledScreenResolution().y, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (!SDL_GL_CreateContext(m_window))
	{
		throw std::runtime_error("Failed to create SDL GL context.");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize OpenGL.");
	}
	
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
	SceneParser sceneParser(&m_resources);
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
	m_scene->Draw();

	SDL_GL_SwapWindow(m_window);
}