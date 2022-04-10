#include "Window.h"

#include <stdexcept>

#include <GL/glew.h>
#include <iostream>

#include "KeybindParser.h"
#include "SceneParser.h"

Window::Window()
{
	m_window = SDL_CreateWindow("3D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, c_defaultWindowSize.x * c_defaultWindowScale, c_defaultWindowSize.y * c_defaultWindowScale, SDL_WINDOW_OPENGL);

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

glm::ivec2 Window::GetWindowSize()
{
	return c_defaultWindowSize;
}

int Window::GetWindowScale()
{
	return c_defaultWindowScale;
}

glm::ivec2 Window::GetScaledWindowSize()
{
	return c_defaultWindowSize * c_defaultWindowScale;
}