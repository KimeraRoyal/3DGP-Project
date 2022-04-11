#include "Material.h"

#include "MaterialParser.h"

size_t Material::s_ambientKey = std::hash<std::string>()("in_Material.ambient");
size_t Material::s_diffuseKey = std::hash<std::string>()("in_Material.diffuse");
size_t Material::s_specularKey = std::hash<std::string>()("in_Material.specular");
size_t Material::s_shininessKey = std::hash<std::string>()("in_Material.shininess");

void Material::Load(const std::string& _path)
{
	MaterialParser materialParser;
	materialParser.Parse(this, _path);
}

void Material::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const
{
	_program->SetUniformValueByKey(s_ambientKey, m_ambient);
	_program->SetUniformValueByKey(s_diffuseKey, m_diffuse);
	_program->SetUniformValueByKey(s_specularKey, m_specular);
	_program->SetUniformValueByKey(s_shininessKey, m_shininess);
}