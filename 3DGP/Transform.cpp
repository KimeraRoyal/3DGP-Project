#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform(const glm::vec3 _position, const glm::quat _rotation, const glm::vec3 _scale)
{
	m_parent = nullptr;
	
	m_position = _position;
	m_rotation = _rotation;
	m_scale = _scale;

	m_model = glm::mat4(1.0f);
	m_dirty = false;
}

Transform::Transform(const glm::vec3 _position, const glm::vec3 _rotation, const glm::vec3 _scale)
	: Transform(_position, glm::quat(glm::radians(_rotation)), _scale) { }

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
		m_model = m_model * glm::mat4_cast(m_rotation);
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
