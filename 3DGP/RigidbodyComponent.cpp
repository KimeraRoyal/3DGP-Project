#include "RigidbodyComponent.h"

#include "Scene.h"
#include "ColliderComponent.h"
#include "ICollider.h"

RigidbodyComponent::RigidbodyComponent()
{
	// Movement
	m_force = glm::vec3(0.0f);
	m_velocity = glm::vec3(0.0f);

	// Rotation
	m_torque = glm::vec3(0.0f);
	m_angularVelocity = glm::vec3(0.0f);
	m_angularMomentum = glm::vec3(0.0f);
	
	m_rotationMatrix = glm::identity<glm::mat3>();
	m_bodyInertia = glm::mat3(0.0f);
	m_inverseInertiaTensor = glm::mat3(0.0f);

	// Material properties
	m_mass = 1.0f;
	m_elasticity = 1.0f;

	m_staticFriction = 0.0f;
	m_dynamicFriction = 0.0f;
}

void RigidbodyComponent::Start()
{
	PhysicsObjectComponent::Start();
	GetScene()->GetPhysicsSystem()->AddRigidbody(std::static_pointer_cast<RigidbodyComponent>(shared_from_this()));
	m_rotationMatrix = glm::mat3_cast(GetTransform()->GetRotation());
	
	// Calculate inverse inertia tensor
	m_bodyInertia = GetCollider()->GetCollider()->CalculateBodyInertia(m_mass);
	CalculateInverseInertiaTensor();
}

std::shared_ptr<IComponent> RigidbodyComponent::GenerateClone()
{
	const std::shared_ptr<RigidbodyComponent> component = std::make_shared<RigidbodyComponent>();
	component->m_mass = m_mass;
	component->m_elasticity = m_elasticity;
	component->m_staticFriction = m_staticFriction;
	component->m_dynamicFriction = m_dynamicFriction;
	return component;
}

void RigidbodyComponent::FixedUpdate(float _deltaTime)
{
	SetSkipCollisionCheck(false);
}

void RigidbodyComponent::PhysicsStep(const float _deltaTime)
{
	// Integration method
	RungeKutta4(_deltaTime);

	// Apply changes
	GetTransform()->Move(m_velocity * _deltaTime);
	UpdateRotation(_deltaTime);

	const glm::quat quatRotation = glm::normalize(glm::quat_cast(m_rotationMatrix));
	m_rotationMatrix = glm::mat3_cast(quatRotation);
	//TODO: Set rotation as quaternion
}

void RigidbodyComponent::Euler(const float _deltaTime)
{
	// Movement
	m_velocity += m_force / m_mass * _deltaTime;
	GetTransform()->Move(m_velocity * _deltaTime);

	// Rotation
	m_angularMomentum += m_torque * _deltaTime;
}

void RigidbodyComponent::RungeKutta2(const float _deltaTime)
{
	// Movement
	glm::vec3 acceleration = glm::vec3(0.0f);
	glm::vec3 k0 = EvaluateRungeKuttaStep(acceleration, glm::vec3(0.0f), _deltaTime);
	glm::vec3 k1 = EvaluateRungeKuttaStep(acceleration, k0 / 2.0f, _deltaTime);

	m_velocity += k1;

	// Rotation
	glm::vec3 torque = m_torque;
	k0 = torque * _deltaTime;

	torque = torque + k0 / 2.0f;
	k1 = torque * _deltaTime;

	m_angularMomentum += k1;
}

void RigidbodyComponent::RungeKutta4(const float _deltaTime)
{
	// Movement
	glm::vec3 acceleration = glm::vec3(0.0f);
	glm::vec3 k0 = EvaluateRungeKuttaStep(acceleration, glm::vec3(0.0f), _deltaTime);
	glm::vec3 k1 = EvaluateRungeKuttaStep(acceleration, k0 / 2.0f, _deltaTime);
	glm::vec3 k2 = EvaluateRungeKuttaStep(acceleration, k1 / 2.0f, _deltaTime);
	glm::vec3 k3 = EvaluateRungeKuttaStep(acceleration, k2, _deltaTime);

	m_velocity += (k0 + k1 * 2.0f + k2 * 2.0f + k3) / 6.0f;

	// Rotation
	glm::vec3 torque = m_torque;
	k0 = torque * _deltaTime;

	torque = m_torque + k0 / 2.0f;
	k1 = torque * _deltaTime;

	torque = m_torque + k1 / 2.0f;
	k2 = torque * _deltaTime;

	torque = m_torque + k2;
	k3 = torque * _deltaTime;

	m_angularMomentum += (k0 + k1 * 2.0f + k2 * 2.0f + k3) / 6.0f;
}

glm::vec3 RigidbodyComponent::EvaluateRungeKuttaStep(glm::vec3& _acceleration, const glm::vec3 _previousStep, const float _deltaTime) const
{
	const glm::vec3 force = m_force + _previousStep;
	_acceleration = force / m_mass;
	return _acceleration * _deltaTime;
}

void RigidbodyComponent::UpdateRotation(const float _deltaTime)
{
	CalculateInverseInertiaTensor();
	m_angularVelocity = m_inverseInertiaTensor * m_angularMomentum;

	const glm::mat3 omegaStar = glm::mat3(
		0.0f, -m_angularVelocity.z, m_angularVelocity.y,
		m_angularVelocity.z, 0.0f, -m_angularVelocity.x,
		-m_angularVelocity.y, m_angularVelocity.x, 0.0f);

	m_rotationMatrix += omegaStar * m_rotationMatrix * _deltaTime;
	GetTransform()->SetRotation(glm::normalize(glm::quat_cast(m_rotationMatrix)));
}

std::shared_ptr<IComponent> RigidbodyComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<RigidbodyComponent> component = std::make_unique<RigidbodyComponent>();

	component->SetMass(_value["mass"].GetFloat());
	component->SetElasticity(_value["elasticity"].GetFloat());
	
	component->SetStaticFriction(_value["staticFriction"].GetFloat());
	component->SetDynamicFriction(_value["dynamicFriction"].GetFloat());

	return std::static_pointer_cast<IComponent>(component);
}
