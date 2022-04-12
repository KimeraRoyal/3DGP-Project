#include "SpotLight.h"

#include "Transform.h"

size_t SpotLight::s_positionKey = std::hash<std::string>()("in_SpotLight.position");
size_t SpotLight::s_directionKey = std::hash<std::string>()("in_SpotLight.direction");

size_t SpotLight::s_ambientKey = std::hash<std::string>()("in_SpotLight.ambient");
size_t SpotLight::s_diffuseKey = std::hash<std::string>()("in_SpotLight.diffuse");
size_t SpotLight::s_specularKey = std::hash<std::string>()("in_SpotLight.specular");

size_t SpotLight::s_innerKey = std::hash<std::string>()("in_SpotLight.innerCutoff");
size_t SpotLight::s_outerKey = std::hash<std::string>()("in_SpotLight.outerCutoff");

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
