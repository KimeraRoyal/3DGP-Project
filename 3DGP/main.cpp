#define SDL_MAIN_HANDLED

#include <memory>

#include "Window.h"

int main()
{
	std::unique_ptr<Window> window = std::make_unique<Window>();
	window->Start();
	window->GameLoop();
	return 0;
}