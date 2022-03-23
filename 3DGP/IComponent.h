#pragma once

#include <memory>
#include "GameObject.h"

class IComponent
{
private:
	friend GameObject;

	std::shared_ptr<GameObject> m_gameObject;

	void SetGameObject(const std::shared_ptr<GameObject>& _gameObject) { m_gameObject = _gameObject; }
protected:
	IComponent() = default;
public:
	virtual ~IComponent() = default;

	virtual void Start() {}
	virtual void Update(const std::shared_ptr<Time>& _time) {}
	virtual void Draw() {}

	[[nodiscard]] std::shared_ptr<GameObject> GetGameObject() const { return m_gameObject; }
};
