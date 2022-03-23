#pragma once

#include <memory>
#include <vector>

#include "Time.h"
#include "Transform.h"

class IComponent;

class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
	Transform m_transform;

	std::vector<std::weak_ptr<IComponent>> m_components;
public:
	void Update(const std::shared_ptr<Time>& _time);

	void AddComponent(const std::shared_ptr<IComponent>& _component);
	
	Transform& GetTransform() { return m_transform; }
};