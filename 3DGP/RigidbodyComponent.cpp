#include "RigidbodyComponent.h"

#include "Resources.h"

std::shared_ptr<IComponent> RigidbodyComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<RigidbodyComponent> component = std::make_unique<RigidbodyComponent>();

	// Set component values

	return std::static_pointer_cast<IComponent>(component);
}
