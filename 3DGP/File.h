#pragma once

#include <string>

class File
{
public:
	static std::string LoadTextFile(const std::string& _path);

	static std::string EvaluatePath(const std::string& _path);
	static std::string GetBasePath();
};

