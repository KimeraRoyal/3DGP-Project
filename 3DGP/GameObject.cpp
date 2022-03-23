#include "GameObject.h"

#include <stdexcept>

#include "IComponent.h"

void GameObject::Update(const std::shared_ptr<Time>& _time)
{
	for (std::weak_ptr<IComponent>& c : m_components)
	{
		std::shared_ptr<IComponent> component = c.lock();
		if (!component) { throw std::runtime_error("Tried to access game object component which no longer exists."); }
		component->Update(_time);
	}
}

void GameObject::AddComponent(const std::shared_ptr<IComponent>& _component)
{
	_component->SetParent(shared_from_this());
	m_components.push_back(_component);
}
