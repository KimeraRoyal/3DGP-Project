#include "Window.h"

#include <stdexcept>

#include <gl/glew.h>

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

	m_triangle = std::make_unique<Triangle>();
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
	return true;
}

void Window::Draw()
{
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	m_triangle->Draw();

	SDL_GL_SwapWindow(m_window);
}