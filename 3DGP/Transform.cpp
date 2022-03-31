#include "Transform.h"


#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform(const glm::vec3 _position, const glm::vec3 _rotation, const glm::vec3 _scale)
{
	m_position = _position;
	m_rotation = _rotation;
	m_scale = _scale;

	m_model = glm::mat4(1.0f);
	m_dirty = false;

	std::cout << "Transform Constructor\n";
}

glm::mat4 Transform::GetModelMatrix() const
{
	if (m_dirty)
	{
		m_model = glm::mat4(1.0f);
		m_model = glm::translate(m_model, m_position);
		m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		m_model = glm::scale(m_model, m_scale);

		m_dirty = false;
	}
	return m_model;
}