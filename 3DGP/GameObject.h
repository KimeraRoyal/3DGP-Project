#pragma once

#include <memory>
#include <vector>

#include "Time.h"
#include "Transform.h"

class Scene;
class IComponent;

class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
	friend Scene;

	static uint32_t s_globalId;

	std::weak_ptr<Scene> m_scene;

	std::vector<std::shared_ptr<IComponent>> m_components;

	Transform m_transform;

	uint32_t m_id;

	GameObject() : m_id(s_globalId++) {}

	std::shared_ptr<Scene> AccessScene() const;
	
	void SetScene(const std::shared_ptr<Scene>& _scene) { m_scene = _scene; }
public:
	bool operator==(const GameObject& _gameObject) const { return m_id == _gameObject.m_id; }
	
	void Start();
	void Update(const std::shared_ptr<Time>& _time);
	void PreDraw();
	
	template<typename T, typename std::enable_if<std::is_base_of<IComponent, T>::value>::type* = nullptr>
	std::shared_ptr<T> AddComponent()
	{
		std::shared_ptr<T> component = std::make_unique<T>();
		AddComponent(component);
		return component;
	}
	
	std::shared_ptr<IComponent> AddComponent(const std::shared_ptr<IComponent>& _component);

	std::shared_ptr<Scene> GetScene() const { return AccessScene(); }
	Transform* GetTransform() { return &m_transform; }

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		for(const std::shared_ptr<IComponent>& component : m_components)
		{
			std::shared_ptr<T> castComponent = std::dynamic_pointer_cast<T>(component);
			if (castComponent) { return castComponent; }
		}
		return nullptr;
	}

	template<typename T>
	void GetComponents(std::vector<std::shared_ptr<T>>& o_components)
	{
		for (const std::shared_ptr<IComponent>& component : m_components)
		{
			std::shared_ptr<T> castComponent = std::dynamic_pointer_cast<T>(component);
			if (castComponent) { o_components.push_back(castComponent); }
		}
	}
};