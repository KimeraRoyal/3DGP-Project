#pragma once
#include "IJsonParser.h"

class Material;

class MaterialParser :	public JsonParser
{
public:
	void Parse(Material* _material, const std::string& _path) const;
};

