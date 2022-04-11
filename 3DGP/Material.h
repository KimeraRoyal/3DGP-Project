#pragma once

#include <memory>
#include <glm/vec3.hpp>

#include "ShaderProgram.h"

class Material : public IResource
{
private:
	static size_t s_ambientKey;
	static size_t s_diffuseKey;
	static size_t s_specularKey;
	static size_t s_shininessKey;
	
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	
	float m_shininess;
public:
	Material()
		: m_ambient(glm::vec3(0.0f)), m_diffuse(glm::vec3(0.0f)), m_specular(glm::vec3(0.0f)), m_shininess(0.0f) {}
	~Material() override = default;
	
	void Load(const std::string& _path) override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const;

	void SetAmbient(const glm::vec3 _ambient) { m_ambient = _ambient; }
	void SetDiffuse(const glm::vec3 _diffuse) { m_diffuse = _diffuse; }
	void SetSpecular(const glm::vec3 _specular) { m_specular = _specular; }
	
	void SetShininess(const float _shininess) { m_shininess = _shininess; }
};
