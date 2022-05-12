#pragma once

#include <string>

#include "JsonParser.h"

class Settings;

class SettingsParser : public JsonParser
{
public:
	void Parse(const std::string& _path, Settings& _settings) const;
};

