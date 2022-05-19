#include "BallComponent.h"

#include <glm/gtc/random.hpp>

#include "GameObject.h"
#include "RigidbodyComponent.h"

void BallComponent::Start()
{
	m_rigidbody = GetGameObject()->GetComponent<RigidbodyComponent>();

	const float torqueBounds = 50.0f;
	m_rigidbody->AddTorque(glm::linearRand(glm::vec3(-torqueBounds), glm::vec3(torqueBounds)));
}

void BallComponent::FixedUpdate(const float _deltaTime)
{
	if (glm::length(m_rigidbody->GetAngularMomentum()) >= 50.0f) { return; }

	const float torqueBounds = 2.0f;
	m_rigidbody->AddTorque(glm::linearRand(glm::vec3(-torqueBounds), glm::vec3(torqueBounds)));
}

std::shared_ptr<IComponent> BallComponent::GenerateClone()
{
	return std::make_shared<BallComponent>();
}

std::shared_ptr<IComponent> BallComponent::Parser::Parse(rapidjson::Value& _value)
{
	return std::static_pointer_cast<IComponent>(std::make_shared<BallComponent>());
}