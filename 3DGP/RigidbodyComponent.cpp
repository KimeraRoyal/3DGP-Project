#include "RigidbodyComponent.h"

#include "Scene.h"
#include "Resources.h"

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

std::shared_ptr<IComponent> RigidbodyComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<RigidbodyComponent> component = std::make_unique<RigidbodyComponent>();

	component->SetMass(_value["mass"].GetFloat());

	return std::static_pointer_cast<IComponent>(component);
}
