#include "SettingsParser.h"

#include "Settings.h"

void SettingsParser::Parse(const std::string& _path, Settings& _settings) const
{
	rapidjson::Document document = ReadDocument(_path);

	_settings.SetScreenResolution(ParseIVector2(document["screenResolution"]));
	_settings.SetScreenScale(document["screenScale"].GetInt());

	_settings.SetPhysicsTimestep(document["physicsTimestep"].GetFloat());
}