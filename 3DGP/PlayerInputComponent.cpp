#include "PlayerInputComponent.h"

size_t PlayerInputComponent::s_horizontalBinding = std::hash<std::string>()("horizontal");
size_t PlayerInputComponent::s_verticalBinding = std::hash<std::string>()("vertical");

PlayerInputComponent::PlayerInputComponent()
{
	m_movementSpeed = 0.0f;
}

void PlayerInputComponent::Update(Time& _time, Input& _input)
{
	const float horizontal = static_cast<float>(_input.GetAxisDown(s_horizontalBinding));
	const float vertical = static_cast<float>(_input.GetAxisDown(s_verticalBinding));
	GetTransform()->Move(glm::vec3(horizontal, 0, -vertical) * (m_movementSpeed * _time.GetDeltaTime()));
}

std::shared_ptr<IComponent> PlayerInputComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<PlayerInputComponent> component = std::make_unique<PlayerInputComponent>();

	component->SetMovementSpeed(_value["speed"].GetFloat());

	return std::static_pointer_cast<IComponent>(component);
}
