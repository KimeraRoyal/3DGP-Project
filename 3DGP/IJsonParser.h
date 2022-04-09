#pragma once

#include <memory>
#include <string>

#include <glm/vec3.hpp>
#include <rapidjson/document.h>

class JsonParser
{
protected:
	rapidjson::Document ReadDocument(const std::string& _path) const;
	
	static glm::vec3 ParseVector(rapidjson::Value& _value);
};

template<class T>
class IJsonParser : public JsonParser
{
public:
	virtual ~IJsonParser() = default;
	
	virtual std::shared_ptr<T> Parse(rapidjson::Value& _value) = 0;
};

