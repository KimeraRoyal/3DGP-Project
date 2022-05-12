#include "SettingsParser.h"

#include "Settings.h"

void SettingsParser::Parse(const std::string& _path, Settings& _settings) const
{
	rapidjson::Document document = ReadDocument(_path);

	_settings.SetScreenResolution(ParseUVector2(document["screenResolution"]));
	_settings.SetScreenScale(document["screenScale"].GetUint());
	
	_settings.SetMultisampleCount(document["multisample"].GetUint());

	_settings.SetPhysicsTimestep(document["physicsTimestep"].GetFloat());
}