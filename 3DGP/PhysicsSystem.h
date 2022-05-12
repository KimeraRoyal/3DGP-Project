#pragma once
#include <memory>
#include <vector>

class RigidbodyComponent;

class PhysicsSystem
{
private:
	float m_timestep;
	
	std::vector<std::shared_ptr<RigidbodyComponent>> m_rigidbodies;
public:
	explicit PhysicsSystem(const float _timestep) : m_timestep(_timestep) {}

	void AddRigidbody(const std::shared_ptr<RigidbodyComponent>& _rigidbody) { m_rigidbodies.push_back(_rigidbody); }

	float GetTimestep() const { return m_timestep; }
};

