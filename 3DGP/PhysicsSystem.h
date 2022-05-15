#pragma once
#include <memory>
#include <vector>

#include <glm/vec3.hpp>

class GameObject;
class RigidbodyComponent;

class Time;

class PhysicsSystem
{
private:
	float m_timestep;

	glm::vec3 m_gravity;
	
	std::vector<std::shared_ptr<RigidbodyComponent>> m_rigidbodies;

	float m_fixedTimer;
public:
	explicit PhysicsSystem(const float _timestep, const glm::vec3 _gravity = glm::vec3(0.0f, -9.8f, 0.0f))
		: m_timestep(_timestep), m_gravity(_gravity), m_fixedTimer(0.0f) {}

	void Update(Time& _time, const std::vector<std::shared_ptr<GameObject>>& _gameObjects);

	void AddRigidbody(const std::shared_ptr<RigidbodyComponent>& _rigidbody) { m_rigidbodies.push_back(_rigidbody); }

	[[nodiscard]] float GetTimestep() const { return m_timestep; }
};

