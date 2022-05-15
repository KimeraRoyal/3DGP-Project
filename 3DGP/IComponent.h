#pragma once

#include <memory>
#include <stdexcept>

class Time;
class Input;

class Scene;
class GameObject;
class Transform;

class IComponent : public std::enable_shared_from_this<IComponent>
{
private:
	friend GameObject;

	std::weak_ptr<GameObject> m_gameObject;

	bool m_gameObjectActive = true;
	bool m_active = true;

	[[nodiscard]] std::shared_ptr<GameObject> AccessGameObject() const
	{
		std::shared_ptr<GameObject> gameObject = m_gameObject.lock();
		if (!gameObject) { throw std::runtime_error("Tried to access component's game object which no longer exists."); }
		return gameObject;
	}

	void SetGameObject(const std::shared_ptr<GameObject>& _gameObject);

	void SetGameObjectActive(const bool _gameObjectActive) { m_gameObjectActive = _gameObjectActive; }
protected:
	IComponent() = default;
public:
	virtual ~IComponent() = default;

	virtual void Start() {}
	virtual void Update(Time& _time, Input& _input) {}
	virtual void FixedUpdate(float _deltaTime) {}

	[[nodiscard]] bool GetActive() const { return m_active && m_gameObjectActive; }

	[[nodiscard]] std::shared_ptr<Scene> GetScene() const;
	[[nodiscard]] std::shared_ptr<GameObject> GetGameObject() const { return AccessGameObject(); }
	[[nodiscard]] Transform* GetTransform() const;

	void SetActive(const bool _active) { m_active = _active; }
};
