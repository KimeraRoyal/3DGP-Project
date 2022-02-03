#include <stdexcept>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <GL/glew.h>

int main()
{
	SDL_Window* window = SDL_CreateWindow("3D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	bool running = true;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}
	}

	SDL_DestroyWindow(window);

	return 0;
}