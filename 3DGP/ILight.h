#pragma once

#include <memory>

#include <glm/vec3.hpp>
#include <memory>

class Transform;
class ShaderProgram;

class ILight
{
private:
	Transform* m_transform;
	
	glm::vec3 m_lightColor;
	float m_lightStrength;
protected:
	friend class LightComponent;
	
	[[nodiscard]] Transform* GetTransform() const { return m_transform; }

	void SetTransform(Transform* _transform) { m_transform = _transform; }
public:
	ILight() : m_transform(nullptr), m_lightColor(glm::vec3(0.0f)), m_lightStrength(0.0f) {}
	virtual ~ILight() = default;

	virtual std::shared_ptr<ILight> GenerateClone() = 0;
	
	virtual void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) = 0;

	[[nodiscard]] glm::vec3 GetLightColor() const { return m_lightColor; }
	[[nodiscard]] float GetLightStrength() const { return m_lightStrength; }

	[[nodiscard]] glm::vec3 GetAmbient() const { return m_lightColor * m_lightStrength * 0.2f; }
	[[nodiscard]] glm::vec3 GetDiffuse() const { return m_lightColor * m_lightStrength; }
	[[nodiscard]] glm::vec3 GetSpecular() const { return glm::vec3(1.0f) * m_lightStrength; }

	void SetLightColor(const glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetLightStrength(const float _lightStrength) { m_lightStrength = _lightStrength; }
};

