#pragma once

#include <memory>
#include <glm/vec3.hpp>

#include "ITexture.h"
#include "ShaderProgram.h"

class Material : public IResource
{
private:
	static size_t s_specularKey;
	static size_t s_shininessKey;

	std::shared_ptr<ITexture> m_diffuse;
	glm::vec3 m_specular;
	
	float m_shininess;
public:
	Material()
		: m_diffuse(nullptr), m_specular(glm::vec3(0.0f)), m_shininess(0.0f) {}
	~Material() override = default;
	
	void Load(const std::string& _path, Resources* _resources) override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const;

	void Bind() const;
	void Unbind() const;

	[[nodiscard]] std::shared_ptr<ITexture> GetDiffuse() const { return m_diffuse; }
	[[nodiscard]] glm::vec3 GetSpecular() const { return m_specular; }
	[[nodiscard]] float GetShininess() const { return m_shininess; }

	void SetDiffuse(const std::shared_ptr<ITexture>& _diffuse) { m_diffuse = _diffuse; }
	void SetSpecular(const glm::vec3 _specular) { m_specular = _specular; }
	void SetShininess(const float _shininess) { m_shininess = _shininess; }

	bool HasTexture() const { return m_diffuse != nullptr; }
};
