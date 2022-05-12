#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <rapidjson/document.h>

class JsonParser
{
protected:
	[[nodiscard]] rapidjson::Document ReadDocument(const std::string& _path) const;

	static glm::vec2 ParseVector2(rapidjson::Value& _value);
	static glm::vec3 ParseVector3(rapidjson::Value& _value);

	static glm::ivec2 ParseIVector2(rapidjson::Value& _value);
	static glm::ivec3 ParseIVector3(rapidjson::Value& _value);
};
