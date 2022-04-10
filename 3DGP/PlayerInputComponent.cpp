#include "PlayerInputComponent.h"

size_t PlayerInputComponent::s_leftBinding = Input::GetBindingKey("left");
size_t PlayerInputComponent::s_rightBinding = Input::GetBindingKey("right");

PlayerInputComponent::PlayerInputComponent()
{
	m_movementSpeed = 0.0f;
}

void PlayerInputComponent::Update(Time& _time, Input& _input)
{
	const float horizontal = static_cast<float>(_input.GetTrinaryBindingDown(s_leftBinding, s_rightBinding));
	GetTransform()->Move(glm::vec3(horizontal * m_movementSpeed, 0, 0) * _time.GetDeltaTime());
}

std::shared_ptr<IComponent> PlayerInputComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<PlayerInputComponent> component = std::make_unique<PlayerInputComponent>();

	component->SetMovementSpeed(_value["speed"].GetFloat());

	return std::static_pointer_cast<IComponent>(component);
}
