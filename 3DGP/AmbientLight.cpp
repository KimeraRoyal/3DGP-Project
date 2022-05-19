#include "AmbientLight.h"

#include "ShaderProgram.h"

size_t AmbientLight::s_ambientKey = std::hash<std::string>()("in_AmbientLight.ambient");

std::shared_ptr<ILight> AmbientLight::GenerateClone()
{
	std::shared_ptr<AmbientLight> clone = std::make_shared<AmbientLight>();
	clone->SetLightColor(GetLightColor());
	clone->SetLightStrength(GetLightStrength());
	return clone;
}

void AmbientLight::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program)
{
	_program->SetUniformValueByKey(s_ambientKey, GetDiffuse());
}
