#pragma once

#include "IComponent.h"
#include "IJsonParser.h"

class RigidbodyComponent;

class BallComponent : public IComponent
{
private:
	std::shared_ptr<RigidbodyComponent> m_rigidbody;

public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	void Start() override;
	void FixedUpdate(float _deltaTime) override;

	std::shared_ptr<IComponent> GenerateClone() override;
};

