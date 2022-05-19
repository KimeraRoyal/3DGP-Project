#pragma once

#include "IComponent.h"
#include "IJsonParser.h"

class BallComponent : public IComponent
{
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	void Start() override;

	std::shared_ptr<IComponent> GenerateClone() override;
};

