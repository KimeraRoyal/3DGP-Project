#include "ColliderComponent.h"

#include "Resources.h"

std::shared_ptr<IComponent> ColliderComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<ColliderComponent> component = std::make_unique<ColliderComponent>();

	// Set component values

	return std::static_pointer_cast<IComponent>(component);
}
