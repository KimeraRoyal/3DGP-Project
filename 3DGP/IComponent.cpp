#include "IComponent.h"

#include "GameObject.h"

void IComponent::SetGameObject(const std::shared_ptr<GameObject>& _gameObject)
{
	m_gameObject = _gameObject;
	m_gameObjectActive = _gameObject->GetActive();
}

std::shared_ptr<Scene> IComponent::GetScene() const
{
	return GetGameObject()->GetScene();
}

Transform* IComponent::GetTransform() const
{
	return AccessGameObject()->GetTransform();
}