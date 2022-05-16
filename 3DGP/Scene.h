#pragma once

#include <memory>

#include "Time.h"
#include "Input.h"

#include "Screen.h"
#include "GameObject.h"

#include "PhysicsSystem.h"
#include "RenderingSystem.h"

class Settings;
class Resources;

class IComponent;

class Scene : public std::enable_shared_from_this<Scene>
{
private:
	Resources* m_resources;
	
	static size_t s_lightPosKey;

	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
	std::vector<std::shared_ptr<GameObject>> m_toDestroy;

	PhysicsSystem m_physicsSystem;
	RenderingSystem m_renderingSystem;
	
	std::shared_ptr<Screen> m_screen;

	void DisposeGameObjects();
public:
	Scene(Settings* _settings, Resources* _resources);

	void Start();
	void Update(Time& _time, Input& _input);
	void Draw();

	std::shared_ptr<GameObject> CreateGameObject();
	void DestroyGameObject(const std::shared_ptr<GameObject>& _gameObject) { m_toDestroy.push_back(_gameObject); }

	template<typename T>
	std::shared_ptr<T> FindComponent()
	{
		for(const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
		{
			std::shared_ptr<T> component = gameObject->GetComponent<T>();
			if (component) { return component; }
		}
		return nullptr;
	}
	
	template<typename T>
	void FindComponents(std::vector<std::shared_ptr<T>>& o_components)
	{
		for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
		{
			gameObject->GetComponents<T>(o_components);
		}
	}

	PhysicsSystem* GetPhysicsSystem() { return &m_physicsSystem; }
	RenderingSystem* GetRenderingSystem() { return &m_renderingSystem; }
};

