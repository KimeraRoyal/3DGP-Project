#include "PointLight.h"

#include "Transform.h"
#include "ShaderProgram.h"

size_t PointLight::s_positionKey = std::hash<std::string>()("in_PointLight.position");

size_t PointLight::s_ambientKey = std::hash<std::string>()("in_PointLight.ambient");
size_t PointLight::s_diffuseKey = std::hash<std::string>()("in_PointLight.diffuse");
size_t PointLight::s_specularKey = std::hash<std::string>()("in_PointLight.specular");

size_t PointLight::s_radiusKey = std::hash<std::string>()("in_PointLight.radius");

void PointLight::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program)
{
	_program->SetUniformValueByKey(s_positionKey, GetTransform()->GetPosition());

	_program->SetUniformValueByKey(s_ambientKey, GetAmbient());
	_program->SetUniformValueByKey(s_diffuseKey, GetDiffuse());
	_program->SetUniformValueByKey(s_specularKey, GetSpecular());
	
	_program->SetUniformValueByKey(s_radiusKey, m_radius);
}
