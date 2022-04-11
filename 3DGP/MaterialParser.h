#pragma once
#include "IJsonParser.h"

class Material;

class MaterialParser :	public JsonParser
{
private:
	Resources* m_resources;
public:
	MaterialParser(Resources* _resources)
		: m_resources(_resources) {}
	void Parse(Material* _material, const std::string& _path) const;
};

