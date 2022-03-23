#include "GameObject.h"

#include <stdexcept>

#include "IComponent.h"

void GameObject::Start()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		AccessComponent(i)->Start();
	}
}

void GameObject::Update(const std::shared_ptr<Time>& _time)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		AccessComponent(i)->Update(_time);
	}
}

void GameObject::Draw()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		AccessComponent(i)->Draw();
	}
}

void GameObject::AddComponent(const std::shared_ptr<IComponent>& _component)
{
	_component->SetGameObject(shared_from_this());
	m_components.push_back(_component);
}

std::shared_ptr<IComponent> GameObject::AccessComponent(const unsigned int _index)
{
	std::shared_ptr<IComponent> component = m_components[_index].lock();
	if (!component) { throw std::runtime_error("Tried to access game object's component which no longer exists."); }
	return component;
}
