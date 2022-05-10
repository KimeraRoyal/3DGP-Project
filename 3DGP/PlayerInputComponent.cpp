#include "PlayerInputComponent.h"

#include "GameObject.h"

size_t PlayerInputComponent::s_horizontalBinding = std::hash<std::string>()("horizontal");
size_t PlayerInputComponent::s_verticalBinding = std::hash<std::string>()("vertical");

PlayerInputComponent::PlayerInputComponent()
{
	m_movementSpeed = 0.0f;
	m_turnSpeed = 0.0f;
}

void PlayerInputComponent::Update(Time& _time, Input& _input)
{
	const float horizontal = static_cast<float>(_input.GetAxisDown(s_horizontalBinding));
	const float vertical = static_cast<float>(_input.GetAxisDown(s_verticalBinding));

	//TODO: Rotate by Quaternion rotation
	const glm::vec3 movementVector = -GetTransform()->GetLeft() * horizontal + GetTransform()->GetForward() * vertical;
	GetTransform()->Move(movementVector * (m_movementSpeed * _time.GetDeltaTime()));
	
	const float rotation = static_cast<float>(_input.GetTrinaryKeyDown(SDL_SCANCODE_Q, SDL_SCANCODE_E));
	GetTransform()->Rotate(glm::vec3(0, rotation,  0) * (-m_turnSpeed * _time.GetDeltaTime()));
}

std::shared_ptr<IComponent> PlayerInputComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<PlayerInputComponent> component = std::make_unique<PlayerInputComponent>();

	component->SetMovementSpeed(_value["speed"].GetFloat());
	component->SetTurnSpeed(_value["turnSpeed"].GetFloat());

	return std::static_pointer_cast<IComponent>(component);
}
