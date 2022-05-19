#include "SpotLight.h"

#include "Transform.h"
#include "ShaderProgram.h"

size_t SpotLight::s_positionKey = std::hash<std::string>()("in_SpotLight.position");
size_t SpotLight::s_directionKey = std::hash<std::string>()("in_SpotLight.direction");

size_t SpotLight::s_ambientKey = std::hash<std::string>()("in_SpotLight.ambient");
size_t SpotLight::s_diffuseKey = std::hash<std::string>()("in_SpotLight.diffuse");
size_t SpotLight::s_specularKey = std::hash<std::string>()("in_SpotLight.specular");

size_t SpotLight::s_innerKey = std::hash<std::string>()("in_SpotLight.innerCutoff");
size_t SpotLight::s_outerKey = std::hash<std::string>()("in_SpotLight.outerCutoff");

std::shared_ptr<ILight> SpotLight::GenerateClone()
{
	std::shared_ptr<SpotLight> clone = std::make_shared<SpotLight>();
	clone->SetLightColor(GetLightColor());
	clone->SetLightStrength(GetLightStrength());
	clone->m_innerCutoff = m_innerCutoff;
	clone->m_outerCutoff = m_outerCutoff;
	return clone;
}

void SpotLight::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program)
{
	_program->SetUniformValueByKey(s_positionKey, GetTransform()->GetPosition());
	_program->SetUniformValueByKey(s_directionKey, GetTransform()->GetForward());

	_program->SetUniformValueByKey(s_ambientKey, GetAmbient());
	_program->SetUniformValueByKey(s_diffuseKey, GetDiffuse());
	_program->SetUniformValueByKey(s_specularKey, GetSpecular());
	
	_program->SetUniformValueByKey(s_innerKey, m_innerCutoff);
	_program->SetUniformValueByKey(s_outerKey, m_outerCutoff);
}
