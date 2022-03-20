#pragma once

#include <string>

class File
{
public:
	static std::string LoadTextFile(const std::string& _fileName);

	static std::string GetBasePath();
};

