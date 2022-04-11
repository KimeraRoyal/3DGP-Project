#pragma once

#include <string>

class Resources;

class IResource
{
public:
	virtual ~IResource() = default;
	
	virtual void Load(const std::string& _path, Resources* _resources) = 0;
};