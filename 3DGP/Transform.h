#pragma once

#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
private:
	Transform* m_parent;
	std::vector<Transform*> m_children;
	
		glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	mutable glm::mat4 m_model;
	mutable bool m_dirty;

	void AddChild(Transform* _child);
	void RemoveChild(Transform* _child);
public:
	explicit Transform(glm::vec3 _position = glm::vec3(0.0f), glm::vec3 _rotation = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f));
	
	Transform(const Transform& _copy) = delete;
	Transform& operator=(const Transform& _other) = delete;

	void Move(const glm::vec3 _amount){ SetPosition(m_position + _amount); }
	void Rotate(const glm::vec3 _amount) { SetRotation(m_rotation += _amount); }

	[[nodiscard]] glm::vec3 GetPosition() const { return m_position; }
	[[nodiscard]] glm::vec3 GetRotation() const { return m_rotation; }
	[[nodiscard]] glm::vec3 GetScale() const { return m_scale; }

	[[nodiscard]] glm::mat4 GetModelMatrix() const;

	void SetParent(Transform* _parent);
	
	void SetPosition(const glm::vec3 _position)
	{
		m_position = _position;
		SetDirty();
	}

	void SetRotation(const glm::vec3 _rotation)
	{
		m_rotation = _rotation;
		SetDirty();
	}

	void SetScale(const glm::vec3 _scale)
	{
		m_scale = _scale;
		SetDirty();
	}

	void SetDirty();
};

