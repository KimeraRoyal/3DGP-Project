#include "MaterialParser.h"

#include "Material.h"

void MaterialParser::Parse(Material* _material, const std::string& _path) const
{
	rapidjson::Document document = ReadDocument(_path);
	
	_material->SetAmbient(ParseVector(document["ambient"]));
	_material->SetDiffuse(ParseVector(document["diffuse"]));
	_material->SetSpecular (ParseVector(document["specular"]));
	
	_material->SetShininess(document["shininess"].GetFloat());
}
