#pragma once

#include <memory>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class GameObject;

class Transform
{
private:
	friend class GameObject;
	
	std::shared_ptr<GameObject> m_gameObject;
	
	Transform* m_parent;
	std::vector<Transform*> m_children;
	
	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;

	mutable glm::mat4 m_model;
	mutable bool m_dirty;

	void SetGameObject(const std::shared_ptr<GameObject>& _gameObject) { m_gameObject = _gameObject; }

	void AddChild(Transform* _child);
	void RemoveChild(Transform* _child);
public:
	explicit Transform(glm::vec3 _position = glm::vec3(0.0f), glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f));
	explicit Transform(glm::vec3 _position = glm::vec3(0.0f), glm::vec3 _rotation = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f));

	void Move(const glm::vec3 _amount){ SetPosition(m_position + _amount); }
	void Rotate(const glm::quat _amount) { SetRotation(m_rotation = m_rotation * _amount); }
	void Rotate(const glm::vec3 _amount) { Rotate(glm::quat(glm::radians(_amount))); }

	std::shared_ptr<GameObject> GetGameObject() const { return m_gameObject; }
	
	Transform* GetParent() const { return m_parent; }
	std::vector<Transform*>& GetChildren() { return m_children; }

	//TODO: Functions to return global position
	[[nodiscard]] glm::vec3 GetPosition() const { return m_position; }
	[[nodiscard]] glm::quat GetRotation() const { return m_rotation; }
	[[nodiscard]] glm::vec3 GetEulerAngles() const { return glm::degrees(glm::eulerAngles(m_rotation)); }
	[[nodiscard]] glm::vec3 GetScale() const { return m_scale; }

	[[nodiscard]] glm::mat4 GetModelMatrix() const;

	[[nodiscard]] glm::vec3 GetLeft() const { return normalize(glm::vec3(GetModelMatrix()[0])); }
	[[nodiscard]] glm::vec3 GetUp() const { return normalize(glm::vec3(GetModelMatrix()[1])); }
	[[nodiscard]] glm::vec3 GetForward() const { return normalize(glm::vec3(GetModelMatrix()[2])); }

	void SetParent(Transform* _parent);
	
	void SetPosition(const glm::vec3 _position)
	{
		m_position = _position;
		SetDirty();
	}

	void SetRotation(const glm::quat _rotation)
	{
		m_rotation = _rotation;
		SetDirty();
	}

	void SetEulerAngles(const glm::vec3 _rotation)
	{
		SetRotation(glm::quat(glm::radians(_rotation)));
	}

	void SetScale(const glm::vec3 _scale)
	{
		m_scale = _scale;
		SetDirty();
	}

	void SetDirty();
};

