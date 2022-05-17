#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Time.h"
#include "Input.h"
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
	std::vector<std::shared_ptr<IComponent>> m_toDestroy;

	Transform m_transform;

	uint32_t m_id;

	bool m_parentActive = true;
	bool m_active = true;

	GameObject() : m_id(s_globalId++) {}
	
	void UpdateChildrenActive();

	void DisposeComponents();

	std::shared_ptr<Scene> AccessScene() const;

	void SetParentActive(const bool _parentActive)
	{
		m_parentActive = _parentActive;
		UpdateChildrenActive();
	}

	void SetScene(const std::shared_ptr<Scene>& _scene) { m_scene = _scene; }
public:
	bool operator==(const GameObject& _gameObject) const { return m_id == _gameObject.m_id; }

	void OnCreate();
	void OnDestroy();
	
	void Start();
	
	void Update(Time& _time, Input& _input);
	void FixedUpdate(float _deltaTime);
	
	template<typename T, typename std::enable_if<std::is_base_of<IComponent, T>::value>::type* = nullptr>
	std::shared_ptr<T> AddComponent()
	{
		std::shared_ptr<T> component = std::make_unique<T>();
		AddComponent(component);
		return component;
	}
	
	std::shared_ptr<IComponent> AddComponent(const std::shared_ptr<IComponent>& _component);
	void RemoveComponent(const std::shared_ptr<IComponent>& _component);

	uint32_t GetId() const { return m_id; }

	bool GetActive() const { return m_active; }

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

	void SetActive(const bool _active)
	{
		m_active = _active;
		UpdateChildrenActive();
	}
};