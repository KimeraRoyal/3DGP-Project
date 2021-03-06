#include "PlayerInputComponent.h"

#include "GameObject.h"
#include "RigidbodyComponent.h"

size_t PlayerInputComponent::s_horizontalBinding = std::hash<std::string>()("horizontal");
size_t PlayerInputComponent::s_verticalBinding = std::hash<std::string>()("vertical");

PlayerInputComponent::PlayerInputComponent()
{
	m_movementSpeed = 0.0f;
	m_turnSpeed = 0.0f;
}

void PlayerInputComponent::Start()
{
	m_rigidbody = GetGameObject()->GetComponent<RigidbodyComponent>();
}

void PlayerInputComponent::Update(Time& _time, Input& _input)
{
	const float horizontal = static_cast<float>(_input.GetAxisDown(s_horizontalBinding));
	const float vertical = static_cast<float>(_input.GetAxisDown(s_verticalBinding));

	const glm::vec3 movementVector = -GetTransform()->GetLeft() * horizontal + GetTransform()->GetForward() * vertical;
	glm::vec3 velocity = m_rigidbody->GetVelocity();
	velocity.x = movementVector.x * m_movementSpeed;
	velocity.z = movementVector.z * m_movementSpeed;
	
	const float rotation = static_cast<float>(_input.GetTrinaryKeyDown(SDL_SCANCODE_Q, SDL_SCANCODE_E));
	m_rigidbody->SetAngularMomentum(glm::vec3(0, rotation,  0) * m_turnSpeed);
	
	m_rigidbody->SetVelocity(velocity);
}

std::shared_ptr<IComponent> PlayerInputComponent::GenerateClone()
{
	const std::shared_ptr<PlayerInputComponent> component = std::make_shared<PlayerInputComponent>();
	component->m_movementSpeed = m_movementSpeed;
	component->m_turnSpeed = m_turnSpeed;
	return component;
}

std::shared_ptr<IComponent> PlayerInputComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<PlayerInputComponent> component = std::make_unique<PlayerInputComponent>();

	component->SetMovementSpeed(_value["speed"].GetFloat());
	component->SetTurnSpeed(_value["turnSpeed"].GetFloat());

	return std::static_pointer_cast<IComponent>(component);
}
