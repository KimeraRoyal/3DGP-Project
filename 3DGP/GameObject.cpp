#include "GameObject.h"

#include <stdexcept>

#include "IComponent.h"

uint32_t GameObject::s_globalId = 0;

void GameObject::OnCreate()
{
	m_transform.SetGameObject(shared_from_this());
}

void GameObject::Start()
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		component->Start();
	}
}

void GameObject::Update(Time& _time, Input& _input)
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		if (!component->GetActive()) { continue; }
		component->Update(_time, _input);
	}
}

std::shared_ptr<IComponent> GameObject::AddComponent(const std::shared_ptr<IComponent>& _component)
{
	_component->SetGameObject(shared_from_this());
	m_components.push_back(_component);
	return _component;
}

std::shared_ptr<Scene> GameObject::AccessScene() const
{
	std::shared_ptr<Scene> scene = m_scene.lock();
	if (!scene) { throw std::runtime_error("Tried to access game object's scene which no longer exists."); }
	return scene;
}

void GameObject::UpdateChildrenActive()
{
	for(const std::shared_ptr<IComponent>& component : m_components)
	{
		component->SetGameObjectActive(m_parentActive && m_active);
	}

	// Cascade changes down to all children
	for(const Transform* child : m_transform.GetChildren())
	{
		child->GetGameObject()->SetParentActive(m_parentActive && m_active);
	}
}