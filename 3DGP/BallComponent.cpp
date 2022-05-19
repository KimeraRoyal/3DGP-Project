#include "BallComponent.h"

#include <glm/gtc/random.hpp>

#include "GameObject.h"
#include "RigidbodyComponent.h"

void BallComponent::Start()
{
	const float torqueBounds = 50.0f;
	GetGameObject()->GetComponent<RigidbodyComponent>()->AddTorque(glm::linearRand(glm::vec3(-torqueBounds), glm::vec3(torqueBounds)));
}

std::shared_ptr<IComponent> BallComponent::GenerateClone()
{
	return std::make_shared<BallComponent>();
}

std::shared_ptr<IComponent> BallComponent::Parser::Parse(rapidjson::Value& _value)
{
	return std::static_pointer_cast<IComponent>(std::make_shared<BallComponent>());
}