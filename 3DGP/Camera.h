#pragma once

#include "IComponent.h"

class Camera : public IComponent
{
private:
	glm::vec3 m_clearColor;
public:
	Camera();

	void Update(const std::shared_ptr<Time>& _time) override;

	void Clear() const;

	[[nodiscard]] glm::mat4 GetViewMatrix() const { return glm::inverse(GetParent()->GetTransform().GetModelMatrix()); }
	[[nodiscard]] glm::vec3 GetClearColor() const { return m_clearColor; }

	void SetClearColor(const glm::vec3 _clearColor) { m_clearColor = _clearColor; }
};