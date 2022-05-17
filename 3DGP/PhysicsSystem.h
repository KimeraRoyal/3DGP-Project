#pragma once
#include <algorithm>
#include <memory>
#include <vector>

#include <glm/vec3.hpp>

struct CollisionInfo;
class GameObject;
class PhysicsObjectComponent;
class RigidbodyComponent;

class Time;

class PhysicsSystem
{
private:
	float m_timestep;

	glm::vec3 m_gravity;
	
	std::vector<std::shared_ptr<RigidbodyComponent>> m_rigidbodies;
	std::vector<std::shared_ptr<PhysicsObjectComponent>> m_physicsObjects;

	float m_fixedTimer;

	void PhysicsStep();

	void ResolveCollisions(const std::shared_ptr<RigidbodyComponent>& _rigidbody);
	void ResolveCollision(const std::shared_ptr<PhysicsObjectComponent>& _a, const std::shared_ptr<PhysicsObjectComponent>& _b, const CollisionInfo& _collision) const;
public:
	explicit PhysicsSystem(const float _timestep, const glm::vec3 _gravity = glm::vec3(0.0f, -9.8f, 0.0f))
		: m_timestep(_timestep), m_gravity(_gravity), m_fixedTimer(0.0f) {}

	void Update(Time& _time, const std::vector<std::shared_ptr<GameObject>>& _gameObjects);
	
	void AddRigidbody(const std::shared_ptr<RigidbodyComponent>& _rigidbody) { m_rigidbodies.push_back(_rigidbody); }
	void AddPhysicsObject(const std::shared_ptr<PhysicsObjectComponent>& _physicsObject) { m_physicsObjects.push_back(_physicsObject); }

	void RemoveRigidbody(const std::shared_ptr<RigidbodyComponent>& _rigidbody) { m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), _rigidbody)); }
	void RemovePhysicsObject(const std::shared_ptr<PhysicsObjectComponent>& _physicsObject) { m_physicsObjects.erase(std::remove(m_physicsObjects.begin(), m_physicsObjects.end(), _physicsObject)); }
	
	[[nodiscard]] float GetTimestep() const { return m_timestep; }
};

