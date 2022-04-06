#pragma once

#include "IJsonParser.h"
#include "IComponent.h"
#include "Resources.h"

class IComponentParser : public IJsonParser<IComponent>
{
protected:
	Resources* m_resources;
public:
	explicit IComponentParser(Resources* _resources);
	~IComponentParser() override = default;
	
	std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override = 0;
};
