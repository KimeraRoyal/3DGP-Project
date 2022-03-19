#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform(const glm::vec3 _position, const glm::vec3 _rotation, const glm::vec3 _scale)
{
	m_position = _position;
	m_rotation = _rotation;
	m_scale = _scale;
}

glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, m_position);
	model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	model = glm::scale(model, m_scale);
	return model;
}