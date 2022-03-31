#pragma once

#include <memory>
#include "GameObject.h"

class IComponent
{
private:
	friend GameObject;

	GameObject* m_gameObject;

	void SetGameObject(GameObject* _gameObject) { m_gameObject = _gameObject; }
protected:
	IComponent() : m_gameObject(nullptr) {}
public:
	virtual ~IComponent() = default;

	virtual void Start() {}
	virtual void Update(const std::shared_ptr<Time>& _time) {}
	virtual void Draw() {}

	virtual void Enable() {}
	virtual void Disable() {}

	[[nodiscard]] GameObject* GetGameObject() const { return m_gameObject; }
	[[nodiscard]] Transform* GetTransform() const { return m_gameObject->GetTransform(); }
};
