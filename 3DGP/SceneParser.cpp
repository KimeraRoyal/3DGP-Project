#include "SceneParser.h"

#include <sstream>

#include <rapidjson/document.h>

#include "CameraComponent.h"
#include "File.h"
#include "ModelComponent.h"

SceneParser::SceneParser(Resources* _resources)
{
	m_resources = _resources;

	m_parsers.insert(std::make_pair("camera", std::make_unique<CameraComponent::Parser>(m_resources)));
	m_parsers.insert(std::make_pair("light", std::make_unique<LightComponent::Parser>(m_resources)));
	m_parsers.insert(std::make_pair("model", std::make_unique<ModelComponent::Parser>(m_resources)));
}

std::shared_ptr<Scene> SceneParser::ParseScene(const std::string& _path)
{
	const std::string sceneText = File::LoadTextFile(File::EvaluatePath(_path));
	
	rapidjson::Document sceneDocument;
	sceneDocument.Parse(sceneText.c_str());
	if (sceneDocument.HasParseError())
	{
#ifdef _DEBUG
		std::stringstream lineStream(sceneText);
		std::string lineSegment, prevLineSegment;
		int lines = 0;
		unsigned int characters = 0;
		while(std::getline(lineStream, lineSegment, '\n'))
		{
			characters += lineSegment.size();
			if (characters >= sceneDocument.GetErrorOffset()) { break; }
			prevLineSegment = lineSegment;
			lines++;
		}
		std::printf("JSON Parse Error: Code %d (%u): \"%s\"\n", sceneDocument.GetParseError(), lines, prevLineSegment.c_str());
#endif
		throw std::runtime_error("Failed to parse JSON scene file! JSON Parse Error, Code: " + sceneDocument.GetParseError());
	}
	
	std::shared_ptr<Scene> scene = std::make_unique<Scene>(m_resources);

	rapidjson::Value& objects = sceneDocument["objects"];
	assert(objects.IsArray());
	for(rapidjson::SizeType i = 0; i < objects.Size(); i++)
	{
		ParseObject(scene, objects[i]);
	}

	return scene;
}

void SceneParser::ParseObject(const std::shared_ptr<Scene>& _scene, rapidjson::Value& _objectValue)
{
	std::shared_ptr<GameObject> gameObject = _scene->CreateGameObject();

	rapidjson::Value& transform = _objectValue["transform"];
	gameObject->GetTransform()->SetPosition(ParseVector(transform["position"]));
	gameObject->GetTransform()->SetRotation(ParseVector(transform["rotation"]));
	gameObject->GetTransform()->SetScale(ParseVector(transform["scale"]));

	rapidjson::Value& components = _objectValue["components"];
	assert(components.IsArray());
	for(rapidjson::SizeType i = 0; i < components.Size(); i++)
	{
		ParseComponent(gameObject, components[i]);
	}
}

void SceneParser::ParseComponent(const std::shared_ptr<GameObject>& _gameObject, rapidjson::Value& _componentValue)
{
	std::shared_ptr<IComponentParser> parser = m_parsers.at(_componentValue["componentType"].GetString());
	_gameObject->AddComponent(parser->Parse(_componentValue));
}
