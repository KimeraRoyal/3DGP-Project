#pragma once

#include <memory>
#include <stdexcept>

#include "GameObject.h"

class IComponent
{
private:
	friend GameObject;

	std::weak_ptr<GameObject> m_gameObject;

	[[nodiscard]] std::shared_ptr<GameObject> AccessGameObject() const
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
	virtual void Update(Time& _time) {}
	virtual void PreDraw() {}

	[[nodiscard]] std::shared_ptr<GameObject> GetGameObject() const { return AccessGameObject(); }
	[[nodiscard]] Transform* GetTransform() const { return AccessGameObject()->GetTransform(); }
};
