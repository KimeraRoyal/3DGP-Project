#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform(const glm::vec3 _position, const glm::vec3 _rotation, const glm::vec3 _scale)
{
	m_position = _position;
	m_rotation = _rotation;
	m_scale = _scale;

	m_model = glm::mat4(1.0f);
	m_dirty = false;
}

void Transform::AddChild(Transform* _child)
{
	m_children.push_back(_child);
}

void Transform::RemoveChild(Transform* _child)
{
	m_children.erase(std::find(m_children.begin(), m_children.end(), _child));
}

glm::mat4 Transform::GetModelMatrix() const
{
	if (m_dirty)
	{
		m_model = glm::mat4(1.0f);
		m_model = glm::translate(m_model, m_position);
		m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		m_model = glm::scale(m_model, m_scale);

		if (m_parent) { m_model = m_parent->GetModelMatrix() * m_model; }

		m_dirty = false;
	}
	return m_model;
}

void Transform::SetParent(Transform* _parent)
{
	if(m_parent) { m_parent->RemoveChild(this); }
	_parent->AddChild(this);
	
	m_parent = _parent;
}

void Transform::SetDirty()
{
	m_dirty = true;
	for(Transform* child : m_children)
	{
		child->SetDirty();
	}
}
