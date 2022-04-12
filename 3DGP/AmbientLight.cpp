#include "AmbientLight.h"

size_t AmbientLight::s_ambientKey = std::hash<std::string>()("in_AmbientLight.ambient");

void AmbientLight::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program)
{
	_program->SetUniformValueByKey(s_ambientKey, GetDiffuse());
}
