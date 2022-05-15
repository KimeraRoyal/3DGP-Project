#include "RigidbodyComponent.h"

#include "Scene.h"

RigidbodyComponent::RigidbodyComponent()
{
	m_force = glm::vec3(0.0f);
	m_velocity = glm::vec3(0.0f);
	m_torque = glm::vec3(0.0f);

	m_mass = 0.0f;
}

void RigidbodyComponent::Start()
{
	GetScene()->GetPhysicsSystem()->AddRigidbody(std::static_pointer_cast<RigidbodyComponent>(shared_from_this()));
}

void RigidbodyComponent::PhysicsStep(const float _deltaTime)
{
	if (GetTransform()->GetPosition().y <= 0.5f)
	{
		const float elasticity = 0.4f;
		const float collisionImpulse = -(1 + elasticity) * glm::dot(m_velocity, glm::vec3(0, 1, 0));
		AddForce(collisionImpulse * glm::vec3(0, 1, 0) / _deltaTime);

		const glm::vec3 contactForce = glm::vec3(0.0f, 9.8f, 0.0f);
		AddForce(contactForce);
	}
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

	return std::static_pointer_cast<IComponent>(component);
}
