#pragma once

#include <memory>
#include <vector>

#include "Time.h"
#include "Transform.h"
#include "Scene.h"

class IComponent;

class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
	friend Scene;

	std::shared_ptr<Scene> m_scene;
	
	Transform m_transform;

	std::vector<std::weak_ptr<IComponent>> m_components;

	std::shared_ptr<IComponent> AccessComponent(unsigned int _index);
	
	void SetScene(const std::shared_ptr<Scene>& _scene) { m_scene = _scene; }
public:
	void Start();
	void Update(const std::shared_ptr<Time>& _time);
	void Draw();
	
	template<typename T, typename std::enable_if<std::is_base_of<IComponent, T>::value>::type* = nullptr>
	std::shared_ptr<T> AddComponent()
	{
		std::shared_ptr<T> component = std::make_unique<T>();
		AddComponent(component);
		return component;
	}
	
	void AddComponent(const std::shared_ptr<IComponent>& _component);

	[[nodiscard]] std::shared_ptr<Scene> GetScene() const { return m_scene; }
	[[nodiscard]] Transform* GetTransform() { return &m_transform; }
};