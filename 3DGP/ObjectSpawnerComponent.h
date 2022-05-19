#pragma once

#include <vector>
#include <glm/vec3.hpp>

#include "IComponent.h"
#include "IJsonParser.h"

class ObjectSpawnerComponent : public IComponent
{
private:
	int m_maxObjects;

	std::string m_prefabName;
	std::shared_ptr<GameObject> m_prefab;

	glm::vec3 m_minSpawnPosition;
	glm::vec3 m_maxSpawnPosition;
	float m_spawnTime;

	std::vector<std::shared_ptr<GameObject>> m_objects;

	float m_timer;
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	ObjectSpawnerComponent();

	void Start() override;

	void Update(Time& _time, Input& _input) override;

	std::shared_ptr<IComponent> GenerateClone() override;

	void SetMaxObjects(const int _maxObjects) { m_maxObjects = _maxObjects; }

	void SetPrefabName(const std::string& _prefabName) { m_prefabName = _prefabName; }

	void SetMinSpawnPosition(const glm::vec3 _minSpawnPosition) { m_minSpawnPosition = _minSpawnPosition; }
	void SetMaxSpawnPosition(const glm::vec3 _maxSpawnPosition) { m_maxSpawnPosition = _maxSpawnPosition; }
	void SetSpawnTime(const float _spawnTime) { m_spawnTime = _spawnTime; }
};

