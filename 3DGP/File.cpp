#include "File.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include <SDL2/SDL_filesystem.h>

std::string File::LoadTextFile(const std::string& _fileName)
{
	const std::string path = GetBasePath() + _fileName;

	std::ifstream fileStream(path);
	std::stringstream buffer;

	buffer << fileStream.rdbuf();
	fileStream.close();

	return buffer.str();
}

std::string File::GetBasePath()
{
	char* sdlBasePath = SDL_GetBasePath();
	std::string basePath = sdlBasePath;
	SDL_free(sdlBasePath);

	return basePath;
}
