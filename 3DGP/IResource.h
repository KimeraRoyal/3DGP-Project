#pragma once

#include <string>

class IResource
{
public:
	virtual ~IResource() = default;
	
	virtual void Load(const std::string& _path) = 0;
};