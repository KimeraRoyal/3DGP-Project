#include "DirectionalLight.h"

#include "Transform.h"
#include "ShaderProgram.h"

size_t DirectionalLight::s_directionKey = std::hash<std::string>()("in_DirLight.direction");

size_t DirectionalLight::s_ambientKey = std::hash<std::string>()("in_DirLight.ambient");
size_t DirectionalLight::s_diffuseKey = std::hash<std::string>()("in_DirLight.diffuse");
size_t DirectionalLight::s_specularKey = std::hash<std::string>()("in_DirLight.specular");

std::shared_ptr<ILight> DirectionalLight::GenerateClone()
{
	std::shared_ptr<DirectionalLight> clone = std::make_shared<DirectionalLight>();
	clone->SetLightColor(GetLightColor());
	clone->SetLightStrength(GetLightStrength());
	return clone;
}

void DirectionalLight::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program)
{
	_program->SetUniformValueByKey(s_directionKey, GetTransform()->GetForward());

	_program->SetUniformValueByKey(s_ambientKey, GetAmbient());
	_program->SetUniformValueByKey(s_diffuseKey, GetDiffuse());
	_program->SetUniformValueByKey(s_specularKey, GetSpecular());
}
