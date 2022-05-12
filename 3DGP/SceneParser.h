#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <GL/glew.h>

#include "IJsonParser.h"

class Settings;

class IComponent;
class Scene;
class GameObject;

class SceneParser : public JsonParser
{
private:
	Settings* m_settings;
	Resources* m_resources;
	
	std::unordered_map<std::string, std::shared_ptr<IJsonParser<IComponent>>> m_parsers;

	void ParseTexture(rapidjson::Value& _textureValue);
	std::shared_ptr<GameObject> ParseObject(const std::shared_ptr<Scene>& _scene, rapidjson::Value& _objectValue);
	void ParseComponent(const std::shared_ptr<GameObject>& _gameObject, rapidjson::Value& _componentValue);

	static GLint GetWrapMode(const std::string& _in);
public:
	SceneParser(Settings* _settings, Resources* _resources);
	
	std::shared_ptr<Scene> Parse(const std::string& _path);
};

