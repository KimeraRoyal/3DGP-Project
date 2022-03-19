#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
private:
	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;
public:
	explicit Transform(glm::vec3 _position = glm::vec3(0.0f), glm::vec3 _rotation = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f));
	
	Transform(const Transform& _copy) = delete;
	Transform& operator=(const Transform& _other) = delete;

	void Move(const glm::vec3 _amount) { m_position += _amount; }

	[[nodiscard]] glm::vec3 GetPosition() const { return m_position; }
	[[nodiscard]] glm::quat GetRotation() const { return m_rotation; }
	[[nodiscard]] glm::vec3 GetScale() const { return m_scale; }

	[[nodiscard]] glm::mat4 GetModelMatrix() const;
	
	void SetPosition(const glm::vec3 _position) { m_position = _position; }
	void SetRotation(const glm::quat _rotation) { m_rotation = _rotation; }
	void SetScale(const glm::vec3 _scale) { m_scale = _scale; }
};

