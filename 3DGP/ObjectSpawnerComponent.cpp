#include "ObjectSpawnerComponent.h"

#include <glm/gtc/random.hpp>

#include "Scene.h"

ObjectSpawnerComponent::ObjectSpawnerComponent()
	: m_maxObjects(0), m_prefabName("spawnObject"),
	m_minSpawnPosition(glm::vec3(0.0f)), m_maxSpawnPosition(glm::vec3(0.0f)),
	m_spawnTime(1.0f), m_timer(0.0f) { }

void ObjectSpawnerComponent::Start()
{
	m_prefab = GetScene()->FindPrefabByName(m_prefabName);
}

void ObjectSpawnerComponent::Update(Time& _time, Input& _input)
{
	if (m_objects.size() >= m_maxObjects) { return; }

	m_timer += _time.GetDeltaTime();
	if (m_timer >= m_spawnTime)
	{
		const glm::vec3 spawnPosition = glm::linearRand(m_minSpawnPosition, m_maxSpawnPosition);
		
		std::shared_ptr<GameObject> newObject = GetScene()->CloneGameObject(m_prefab);
		newObject->GetTransform()->SetPosition(spawnPosition);
		m_objects.push_back(newObject);

		m_timer -= m_spawnTime;
	}
}

std::shared_ptr<IComponent> ObjectSpawnerComponent::GenerateClone()
{
	const std::shared_ptr<ObjectSpawnerComponent> component = std::make_shared<ObjectSpawnerComponent>();
	component->m_maxObjects = m_maxObjects;
	component->m_prefab = m_prefab;
	component->m_minSpawnPosition = m_minSpawnPosition;
	component->m_maxSpawnPosition = m_maxSpawnPosition;
	component->m_spawnTime = m_spawnTime;
	return component;
}

std::shared_ptr<IComponent> ObjectSpawnerComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<ObjectSpawnerComponent> component = std::make_unique<ObjectSpawnerComponent>();

	component->SetMaxObjects(_value["maxObjects"].GetInt());

	component->SetPrefabName(_value["prefab"].GetString());
	
	component->SetMinSpawnPosition(ParseVector3(_value["minSpawnPosition"]));
	component->SetMaxSpawnPosition(ParseVector3(_value["maxSpawnPosition"]));
	component->SetSpawnTime(_value["spawnTime"].GetFloat());

	return std::static_pointer_cast<IComponent>(component);
}