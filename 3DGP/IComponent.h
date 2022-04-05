#pragma once

#include <memory>
#include <stdexcept>

#include "GameObject.h"

class IComponent
{
private:
	friend GameObject;

	std::weak_ptr<GameObject> m_gameObject;

	std::shared_ptr<GameObject> AccessGameObject() const
	{
		std::shared_ptr<GameObject> gameObject = m_gameObject.lock();
		if (!gameObject) { throw std::runtime_error("Tried to access component's game object which no longer exists."); }
		return gameObject;
	}

	void SetGameObject(const std::shared_ptr<GameObject>& _gameObject) { m_gameObject = _gameObject; }
protected:
	IComponent() = default;
public:
	virtual ~IComponent() = default;

	virtual void Start() {}
	virtual void Update(const std::shared_ptr<Time>& _time) {}
	virtual void PreDraw() {}

	std::shared_ptr<GameObject> GetGameObject() const { return AccessGameObject(); }
	Transform* GetTransform() const { return AccessGameObject()->GetTransform(); }
};
