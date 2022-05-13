#include "SettingsParser.h"

#include "Settings.h"

void SettingsParser::Parse(const std::string& _path, Settings& _settings) const
{
	rapidjson::Document document = ReadDocument(_path);

	_settings.SetControlWindowMovement(document["controlWindowMovement"].GetBool());
	_settings.SetWindowAnchor(ParseVector2(document["windowAnchor"]));
	_settings.SetWindowPosition(ParseVector2(document["windowPosition"]));

	_settings.SetWindowResolution(ParseUVector2(document["screenResolution"]));
	_settings.SetWindowScale(document["screenScale"].GetUint());
	
	_settings.SetMultisampleCount(document["multisample"].GetUint());

	_settings.SetPhysicsTimestep(document["physicsTimestep"].GetFloat());
}