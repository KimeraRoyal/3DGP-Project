#include "StaticbodyComponent.h"

std::shared_ptr<IComponent> StaticbodyComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<StaticbodyComponent> component = std::make_unique<StaticbodyComponent>();

	// Set variables

	return std::static_pointer_cast<IComponent>(component);
}