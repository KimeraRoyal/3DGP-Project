#pragma once

#include <glm/mat3x3.hpp>

#include "PhysicsObjectComponent.h"
#include "IJsonParser.h"

#include "CollisionInfo.h"

class Resources;
class ColliderComponent;

class RigidbodyComponent : public PhysicsObjectComponent
{
private:
	// Movement
	glm::vec3 m_force;
	glm::vec3 m_velocity;

	// Rotation
	glm::vec3 m_torque;
	glm::vec3 m_angularVelocity;
	glm::vec3 m_angularMomentum;

	glm::mat3 m_rotationMatrix;
	glm::mat3 m_bodyInertia;
	glm::mat3 m_inverseInertiaTensor;

	// Material properties
	float m_mass;
	float m_elasticity;

	float m_staticFriction;
	float m_dynamicFriction;

	// Integration methods
	void Euler(float _deltaTime);
	void RungeKutta2(float _deltaTime);
	void RungeKutta4(float _deltaTime);

	glm::vec3 EvaluateRungeKuttaStep(glm::vec3& _acceleration, glm::vec3 _previousStep, float _deltaTime) const;

	void UpdateRotation(float _deltaTime);

	void CalculateInverseInertiaTensor() { m_inverseInertiaTensor = m_rotationMatrix * glm::inverse(m_bodyInertia) * glm::transpose(m_rotationMatrix); }
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	RigidbodyComponent();

	void Start() override;
	void FixedUpdate(float _deltaTime) override;

	void PhysicsStep(float _deltaTime);

	void AddForce(const glm::vec3 _force) override { m_force += m_mass * _force; }
	void AddTorque(const glm::vec3 _torque) override { m_torque += _torque; }

	void ClearForce() { SetForce(glm::vec3(0.0f)); }
	void ClearTorque() { SetTorque(glm::vec3(0.0f)); }

	bool GetIsDynamic() override { return true; }

	glm::vec3 GetForce() override { return m_force; }
	glm::vec3 GetVelocity() override { return m_velocity; }
	glm::vec3 GetTorque() const { return m_torque; }

	glm::vec3 GetAngularMomentum() override { return m_angularMomentum; }
	
	float GetMass() override { return m_mass; }
	float GetElasticity() override { return m_elasticity; }

	float GetStaticFriction() override { return m_staticFriction; }
	float GetDynamicFriction() override { return m_dynamicFriction; }

	void SetForce(const glm::vec3 _force) { m_force = _force; }
	void SetVelocity(const glm::vec3 _velocity) override { m_velocity = _velocity; }
	void SetTorque(const glm::vec3 _torque) { m_torque = _torque; }

	void SetAngularMomentum(const glm::vec3 _angularMomentum) { m_angularMomentum = _angularMomentum; }
	
	void SetMass(const float _mass) { m_mass = _mass; }
	void SetElasticity(const float _elasticity) { m_elasticity = _elasticity; }

	void SetStaticFriction(const float _staticFriction) { m_staticFriction = _staticFriction; }
	void SetDynamicFriction(const float _dynamicFriction) { m_dynamicFriction = _dynamicFriction; }
};

