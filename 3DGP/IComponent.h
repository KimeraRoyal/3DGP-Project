#pragma once

#include <memory>
#include "GameObject.h"

class IComponent
{
private:
	friend GameObject;

	std::shared_ptr<GameObject> m_parent;

	void SetParent(const std::shared_ptr<GameObject>& _parent) { m_parent = _parent; }
public:
	virtual ~IComponent() = default;
	
	virtual void Update(const std::shared_ptr<Time>& _time) = 0;

	[[nodiscard]] std::shared_ptr<GameObject> GetParent() const { return m_parent; }
};
