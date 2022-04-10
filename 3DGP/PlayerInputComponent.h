#pragma once
#include "IComponent.h"
#include "IComponentParser.h"

class PlayerInputComponent :
    public IComponent
{
private:
	static size_t s_leftBinding;
	static size_t s_rightBinding;
	
	float m_movementSpeed;
public:
	PlayerInputComponent();
	void Update(Time& _time, Input& _input) override;
	
	class Parser final : public IComponentParser
	{
	public:
		explicit Parser(Resources* _resources) : IComponentParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	void SetMovementSpeed(const float _movementSpeed) { m_movementSpeed = _movementSpeed; }
};

