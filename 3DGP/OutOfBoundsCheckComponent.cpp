#include "OutOfBoundsCheckComponent.h"

#include <glm/gtc/random.hpp>

#include "GameObject.h"
#include "RigidbodyComponent.h"

void OutOfBoundsCheckComponent::Start()
{
	m_rigidbody = GetGameObject()->GetComponent<RigidbodyComponent>();
}

void OutOfBoundsCheckComponent::Update(Time& _time, Input& _input)
{
	if (GetTransform()->GetPosition().y < m_minHeight)
	{
		const glm::vec3 resetPosition = glm::linearRand(m_minResetPosition, m_maxResetPosition);
		GetTransform()->SetPosition(resetPosition);
		m_rigidbody->SetVelocity(glm::vec3(glm::linearRand(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
	}
}

std::shared_ptr<IComponent> OutOfBoundsCheckComponent::GenerateClone()
{
	const std::shared_ptr<OutOfBoundsCheckComponent> component = std::make_shared<OutOfBoundsCheckComponent>();
	component->m_minHeight = m_minHeight;
	component->m_minResetPosition = m_minResetPosition;
	component->m_maxResetPosition = m_maxResetPosition;
	return component;
}

std::shared_ptr<IComponent> OutOfBoundsCheckComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<OutOfBoundsCheckComponent> component = std::make_unique<OutOfBoundsCheckComponent>();

	component->SetMinHeight(_value["minHeight"].GetFloat());
	
	if (_value.HasMember("resetPosition")) { component->SetResetPosition(ParseVector3(_value["resetPosition"])); }
	else
	{
		component->SetMinResetPosition(ParseVector3(_value["minResetPosition"]));
		component->SetMaxResetPosition(ParseVector3(_value["maxResetPosition"]));
	}

	return std::static_pointer_cast<IComponent>(component);
}