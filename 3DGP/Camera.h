#pragma once

#include "Transform.h"

class Camera
{
private:
	Transform m_transform;

	glm::vec3 m_clearColor;
public:
	Camera();
	
	Transform* GetTransform() { return &m_transform; }

	[[nodiscard]] glm::vec3 GetClearColor() const { return m_clearColor; }

	void SetClearColor(const glm::vec3 _clearColor) { m_clearColor = _clearColor; }
};