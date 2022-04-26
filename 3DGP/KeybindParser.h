#pragma once

#include <string>

#include "IJsonParser.h"

class Input;

class KeybindParser : public JsonParser
{
private:
	void ParseBindings(rapidjson::Value& _bindings, Input& _input) const;
	void ParseAxis(rapidjson::Value& _axis, Input& _input) const;
public:
	void Parse(const std::string& _path, Input& _input) const;
};
