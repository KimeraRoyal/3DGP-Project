#pragma once

#include <memory>
#include <string>

#include "IComponentParser.h"
#include "Scene.h"

class SceneParser : public JsonParser
{
private:
	Resources* m_resources;
	
	std::unordered_map<std::string, std::shared_ptr<IComponentParser>> m_parsers;

	void ParseObject(const std::shared_ptr<Scene>& _scene, rapidjson::Value& _objectValue);
	void ParseComponent(const std::shared_ptr<GameObject>& _gameObject, rapidjson::Value& _componentValue);
public:
	SceneParser(Resources* _resources);
	
	std::shared_ptr<Scene> ParseScene(const std::string& _path);
};

