#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <rapidjson/document.h>

class JsonParser
{
protected:
	[[nodiscard]] rapidjson::Document ReadDocument(const std::string& _path) const;

	static glm::vec3 ParseVector(rapidjson::Value& _value);
};
