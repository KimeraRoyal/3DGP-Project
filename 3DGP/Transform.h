#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	mutable glm::mat4 m_model;
	mutable bool m_dirty;
public:
	explicit Transform(glm::vec3 _position = glm::vec3(0.0f), glm::vec3 _rotation = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f));
	
	Transform(const Transform& _copy) = delete;
	Transform& operator=(const Transform& _other) = delete;

	void Move(const glm::vec3 _amount) { m_position += _amount; }
	void Rotate(const glm::vec3 _amount) { m_rotation += _amount; }

	[[nodiscard]] glm::vec3 GetPosition() const { return m_position; }
	[[nodiscard]] glm::vec3 GetRotation() const { return m_rotation; }
	[[nodiscard]] glm::vec3 GetScale() const { return m_scale; }

	[[nodiscard]] glm::mat4 GetModelMatrix() const;
	
	void SetPosition(const glm::vec3 _position)
	{
		m_position = _position;
		m_dirty = true;
	}

	void SetRotation(const glm::vec3 _rotation)
	{
		m_rotation = _rotation;
		m_dirty = true;
	}

	void SetScale(const glm::vec3 _scale)
	{
		m_scale = _scale;
		m_dirty = true;
	}
};

