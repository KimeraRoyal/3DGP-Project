#include "Window.h"

#include <stdexcept>

#include <GL/glew.h>
#include <iostream>

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

	m_time = std::make_unique<Time>();

	m_triangle = std::make_unique<Scene>();
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

bool Window::PollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}

	return true;
}

bool Window::Update()
{
	m_time->Update();

	return true;
}

void Window::Draw()
{
	glClearColor(0.7f, 0.5f, 0.8f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_triangle->Draw(m_time);

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