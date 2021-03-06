#pragma once

#include "IComponent.h"
#include "IJsonParser.h"
#include "RenderableComponent.h"
#include "LightComponent.h"

class CameraComponent final : public IComponent
{
private:
	static size_t s_viewKey;
	static size_t s_projectionKey;
	static size_t s_viewPosKey;
	
	glm::vec3 m_clearColor;

	float m_fov;
	
	float m_nearPlane;
	float m_farPlane;
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};
	
	CameraComponent();

	void Start() override;
	void DrawRenderables(const std::vector<std::shared_ptr<RenderableComponent>>& _renderables) const;

	void Clear() const;

	std::shared_ptr<IComponent> GenerateClone() override;

	[[nodiscard]] glm::mat4 GetViewMatrix() const;
	
	[[nodiscard]] glm::vec3 GetClearColor() const { return m_clearColor; }

	[[nodiscard]] float GetFOV() const { return m_fov; }
	
	[[nodiscard]] float GetNearPlane() const { return m_nearPlane; }
	[[nodiscard]] float GetFarPlane() const { return m_farPlane; }

	void SetClearColor(const glm::vec3 _clearColor) { m_clearColor = _clearColor; }
	
	void SetFOV(const float _fov) { m_fov = _fov; }
	
	void SetNearPlane(const float _nearPlane) { m_nearPlane = _nearPlane; }
	void SetFarPlane(const float _farPlane) { m_farPlane = _farPlane; }
};
