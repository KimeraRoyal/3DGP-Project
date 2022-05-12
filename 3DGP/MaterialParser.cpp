#include "MaterialParser.h"

#include "Resources.h"
#include "Material.h"

void MaterialParser::Parse(Material* _material, const std::string& _path) const
{
	rapidjson::Document document = ReadDocument(_path);

	if(document.HasMember("diffuse"))
	{
		const std::string diffuse = document["diffuse"].GetString();
		if (!diffuse.empty()) { _material->SetDiffuse(m_resources->GetTexture(diffuse)); }
	}
	_material->SetSpecular(ParseVector3(document["specular"]));
	
	_material->SetShininess(document["shininess"].GetFloat());
}
