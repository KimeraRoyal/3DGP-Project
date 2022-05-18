#include "RigidbodyComponent.h"

#include "Scene.h"
#include "ColliderComponent.h"
#include "ICollider.h"

RigidbodyComponent::RigidbodyComponent()
{
	m_force = glm::vec3(0.0f);
	m_velocity = glm::vec3(0.0f);
	m_torque = glm::vec3(0.0f);

	m_mass = 1.0f;
	m_elasticity = 1.0f;

	m_staticFriction = 0.0f;
	m_dynamicFriction = 0.0f;
}

void RigidbodyComponent::Start()
{
	PhysicsObjectComponent::Start();
	GetScene()->GetPhysicsSystem()->AddRigidbody(std::static_pointer_cast<RigidbodyComponent>(shared_from_this()));
}

void RigidbodyComponent::PhysicsStep(const float _deltaTime)
{
	Euler(_deltaTime);
}

void RigidbodyComponent::Euler(const float _deltaTime)
{
	// Position
	m_velocity += m_force / m_mass * _deltaTime;
	GetTransform()->Move(m_velocity * _deltaTime);

	// Rotation
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
