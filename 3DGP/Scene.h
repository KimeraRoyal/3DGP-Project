#pragma once

#include <memory>

#include "Time.h"

#include "Screen.h"
#include "GameObject.h"
#include "Resources.h"

class IComponent;

class Scene : public std::enable_shared_from_this<Scene>
{
private:
	Resources* m_resources;
	
	static size_t s_lightPosKey;

	std::vector<std::shared_ptr<GameObject>> m_gameObjects;

	std::shared_ptr<Screen> m_screen;
public:
	Scene(Resources* _resources);

	void Start();
	void Update(Time& _time);
	void Draw();

	std::shared_ptr<GameObject> CreateGameObject();

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
};

