#pragma once

#include <string>

#include "IJsonParser.h"
#include "Input.h"

class KeybindParser : public JsonParser
{
public:
	void Parse(const std::string& _path, Input& _input) const;
};
