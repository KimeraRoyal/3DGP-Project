#pragma once

#include "IComponent.h"
#include "IRenderable.h"

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

	std::vector<std::shared_ptr<IRenderable>> m_renderables;
public:
	CameraComponent();

	void Start() override;
	void Update(const std::shared_ptr<Time>& _time) override;
	void PreDraw() override;

	void Clear() const;

	[[nodiscard]] glm::mat4 GetViewMatrix() const { return glm::inverse(GetGameObject()->GetTransform()->GetModelMatrix()); }
	[[nodiscard]] glm::vec3 GetClearColor() const { return m_clearColor; }

	void SetClearColor(const glm::vec3 _clearColor) { m_clearColor = _clearColor; }
};
