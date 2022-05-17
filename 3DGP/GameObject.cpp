#include "GameObject.h"

#include <stdexcept>

#include "IComponent.h"

uint32_t GameObject::s_globalId = 0;

void GameObject::OnCreate()
{
	m_transform.SetGameObject(shared_from_this());

	for (std::shared_ptr<IComponent>& component : m_components)
	{
		component->OnCreate();
	}
}

void GameObject::OnDestroy()
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		component->OnDestroy();
	}
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
	DisposeComponents();
}

void GameObject::FixedUpdate(const float _deltaTime)
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		if (!component->GetActive()) { continue; }
		component->FixedUpdate(_deltaTime);
	}
}

void GameObject::UpdateChildrenActive()
{
	for (const std::shared_ptr<IComponent>& component : m_components)
	{
		component->SetGameObjectActive(m_parentActive && m_active);
	}

	// Cascade changes down to all children
	for (const Transform* child : m_transform.GetChildren())
	{
		child->GetGameObject()->SetParentActive(m_parentActive && m_active);
	}
}

std::shared_ptr<IComponent> GameObject::AddComponent(const std::shared_ptr<IComponent>& _component)
{
	_component->SetGameObject(shared_from_this());
	m_components.push_back(_component);
	//if (m_started) { _component->Start(); } //TODO: Implement to add vector and start check
	return _component;
}

void GameObject::RemoveComponent(const std::shared_ptr<IComponent>& _component)
{
	if(std::count(m_components.begin(), m_components.end(), _component)) { m_toDestroy.push_back(_component); }
	else { throw std::runtime_error("Attempted to remove a component which does not exist on this game object."); }
}

void GameObject::DisposeComponents()
{
	if (m_toDestroy.empty()) { return; }

	for (const std::shared_ptr<IComponent>& component : m_toDestroy)
	{
		component->OnDestroy();
		m_components.erase(std::remove(m_components.begin(), m_components.end(), component));
	}
	m_toDestroy.clear();
}

std::shared_ptr<Scene> GameObject::AccessScene() const
{
	std::shared_ptr<Scene> scene = m_scene.lock();
	if (!scene) { throw std::runtime_error("Tried to access game object's scene which no longer exists."); }
	return scene;
}