#pragma once

#include "IComponent.h"
#include "IJsonParser.h"

class Resources;

class RigidbodyComponent : public IComponent
{
private:
	glm::vec3 m_force;
	glm::vec3 m_velocity;
	glm::vec3 m_torque;

	float m_mass;

	// Integration methods
	void Euler(float _deltaTime);
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	RigidbodyComponent();

	void Start() override;

	void PhysicsStep(float _deltaTime);

	void AddForce(const glm::vec3 _force) { m_force += m_mass * _force; }
	void AddTorque(const glm::vec3 _torque) { m_torque += _torque; }

	void ClearForce() { SetForce(glm::vec3(0.0f)); }
	void ClearTorque() { SetTorque(glm::vec3(0.0f)); }

	glm::vec3 GetForce() const { return m_force; }
	glm::vec3 GetVelocity() const { return m_velocity; }
	glm::vec3 GetTorque() const { return m_torque; }
	
	float GetMass() const { return m_mass; }

	void SetForce(const glm::vec3 _force) { m_force = _force; }
	void SetVelocity(const glm::vec3 _velocity) { m_velocity = _velocity; }
	void SetTorque(const glm::vec3 _torque) { m_torque = _torque; }
	
	void SetMass(const float _mass) { m_mass = _mass; }
};

