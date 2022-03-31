#include "GameObject.h"

#include <stdexcept>

#include "IComponent.h"

uint32_t GameObject::s_globalId = 0;

void GameObject::Start()
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		component->Start();
	}
}

void GameObject::Update(const std::shared_ptr<Time>& _time)
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		component->Update(_time);
	}
}

void GameObject::Draw()
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		component->Draw();
	}
}

void GameObject::Disable()
{
	for (std::shared_ptr<IComponent>& component : m_components)
	{
		component->Disable();
	}
	m_components.clear();
}

std::shared_ptr<IComponent> GameObject::AddComponent(const std::shared_ptr<IComponent>& _component)
{
	_component->SetGameObject(this);
	m_components.push_back(_component);
	return _component;
}

std::shared_ptr<Scene> GameObject::AccessScene() const
{
	std::shared_ptr<Scene> scene = m_scene.lock();
	if (!scene) { throw std::runtime_error("Tried to access game object's component which no longer exists."); }
	return scene;
}