#pragma once

#include <string>

class File
{
private:
	static std::string GetBasePath();
public:
	static std::string LoadTextFile(const std::string& _fileName);
};

