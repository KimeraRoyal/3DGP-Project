#pragma once

#include <memory>
#include <string>

#include "IJsonParser.h"
#include "Scene.h"

class SceneParser : public JsonParser
{
private:
	Resources* m_resources;
	
	std::unordered_map<std::string, std::shared_ptr<IJsonParser<IComponent>>> m_parsers;

	void ParseTexture(rapidjson::Value& _textureValue);
	void ParseObject(const std::shared_ptr<Scene>& _scene, rapidjson::Value& _objectValue);
	void ParseComponent(const std::shared_ptr<GameObject>& _gameObject, rapidjson::Value& _componentValue);

	static GLint GetWrapMode(const std::string& _in);
public:
	SceneParser(Resources* _resources);
	
	std::shared_ptr<Scene> Parse(const std::string& _path);
};

