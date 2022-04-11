#include "Material.h"

#include "MaterialParser.h"

size_t Material::s_specularKey = std::hash<std::string>()("in_Material.specular");
size_t Material::s_shininessKey = std::hash<std::string>()("in_Material.shininess");

void Material::Load(const std::string& _path, Resources* _resources)
{
	const MaterialParser materialParser(_resources);
	materialParser.Parse(this, _path);
}

void Material::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const
{
	_program->SetUniformValueByKey(s_specularKey, m_specular);
	_program->SetUniformValueByKey(s_shininessKey, m_shininess);
}

void Material::Bind() const
{
	if (m_diffuse) { m_diffuse->Bind(); }
}

void Material::Unbind() const
{
	if (m_diffuse) { m_diffuse->Unbind(); }
}
