#pragma once

#include "PhysicsObjectComponent.h"
#include "IJsonParser.h"

#include "CollisionInfo.h"

class Resources;
class ColliderComponent;

class RigidbodyComponent : public PhysicsObjectComponent
{
private:
	glm::vec3 m_force;
	glm::vec3 m_velocity;
	glm::vec3 m_torque;

	float m_mass;
	float m_elasticity;

	float m_staticFriction;
	float m_dynamicFriction;

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

	void AddForce(const glm::vec3 _force) override { m_force += m_mass * _force; }
	void AddTorque(const glm::vec3 _torque) { m_torque += _torque; }

	void ClearForce() { SetForce(glm::vec3(0.0f)); }
	void ClearTorque() { SetTorque(glm::vec3(0.0f)); }

	bool GetIsDynamic() override { return true; }

	glm::vec3 GetForce() const { return m_force; }
	glm::vec3 GetVelocity() override { return m_velocity; }
	glm::vec3 GetTorque() const { return m_torque; }
	
	float GetMass() override { return m_mass; }
	float GetElasticity() override { return m_elasticity; }

	float GetStaticFriction() override { return m_staticFriction; }
	float GetDynamicFriction() override { return m_dynamicFriction; }

	void SetForce(const glm::vec3 _force) { m_force = _force; }
	void SetVelocity(const glm::vec3 _velocity) override { m_velocity = _velocity; }
	void SetTorque(const glm::vec3 _torque) { m_torque = _torque; }
	
	void SetMass(const float _mass) { m_mass = _mass; }
	void SetElasticity(const float _elasticity) { m_elasticity = _elasticity; }

	void SetStaticFriction(const float _staticFriction) { m_staticFriction = _staticFriction; }
	void SetDynamicFriction(const float _dynamicFriction) { m_dynamicFriction = _dynamicFriction; }
};

