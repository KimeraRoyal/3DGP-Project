#pragma once
#include "IComponent.h"
#include "IJsonParser.h"

class RigidbodyComponent;

class PlayerInputComponent : public IComponent
{
private:
	static size_t s_horizontalBinding;
	static size_t s_verticalBinding;
	
	float m_movementSpeed;
	float m_turnSpeed;
public:
	PlayerInputComponent();

	void Start() override;
	
	void Update(Time& _time, Input& _input) override;
	
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	void SetMovementSpeed(const float _movementSpeed) { m_movementSpeed = _movementSpeed; }
	void SetTurnSpeed(const float _turnSpeed) { m_turnSpeed = _turnSpeed; }
};

