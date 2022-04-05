#include "File.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include <SDL2/SDL_filesystem.h>

std::string File::LoadTextFile(const std::string& _path)
{
	std::ifstream fileStream(_path);
	std::stringstream buffer;

	buffer << fileStream.rdbuf();
	fileStream.close();

	return buffer.str();
}

std::string File::EvaluatePath(const std::string& _path)
{
	const std::filesystem::path filePath(_path);
	if (filePath.is_relative())
	{
		return GetBasePath() + _path;
	}

	return _path;
}

std::string File::GetBasePath()
{
	char* sdlBasePath = SDL_GetBasePath();
	std::string basePath = sdlBasePath;
	SDL_free(sdlBasePath);

	return basePath;
}
