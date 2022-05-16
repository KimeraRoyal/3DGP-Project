#pragma once

#include "PhysicsObjectComponent.h"
#include "IJsonParser.h"

class StaticbodyComponent : public PhysicsObjectComponent
{
private:
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};
	
	bool GetIsDynamic() override { return false; }
};

