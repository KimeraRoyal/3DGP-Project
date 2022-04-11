#pragma once
#include "IComponent.h"
#include "IJsonParser.h"

class PlayerInputComponent :
    public IComponent
{
private:
	static size_t s_horizontalBinding;
	static size_t s_verticalBinding;
	
	float m_movementSpeed;
public:
	PlayerInputComponent();
	void Update(Time& _time, Input& _input) override;
	
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	void SetMovementSpeed(const float _movementSpeed) { m_movementSpeed = _movementSpeed; }
};

