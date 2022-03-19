#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(const glm::vec3 _position, const glm::vec3 _scale)
{
	m_position = _position;
	m_scale = _scale;
}

glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, m_position);
	model = glm::scale(model, m_scale);
	// model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return model;
}