#pragma once

#include <memory>

#include "JsonParser.h"

class Resources;

template<class T>
class IJsonParser : public JsonParser
{
protected:
	Resources* m_resources;
public:
	IJsonParser(Resources* _resources)
		: m_resources(_resources) {}
	virtual ~IJsonParser() = default;
	
	virtual std::shared_ptr<T> Parse(rapidjson::Value& _value) = 0;
};

