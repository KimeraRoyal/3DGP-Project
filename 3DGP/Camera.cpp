#include "Camera.h"

#include <GL/glew.h>

Camera::Camera()
{
	m_clearColor = glm::vec3(0.0f);
}

void Camera::Update(const std::shared_ptr<Time>& _time)
{
	
}

void Camera::Clear() const
{
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
