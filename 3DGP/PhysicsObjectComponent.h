#pragma once

#include <glm/vec3.hpp>

#include "CollisionInfo.h"
#include "IComponent.h"

class ColliderComponent;

class PhysicsObjectComponent : public IComponent
{
private:
	std::shared_ptr<ColliderComponent> m_collider;

	bool m_skipCollisionCheck = false;
public:
	void Start() override;
	void FixedUpdate(float _deltaTime) override;

	CollisionInfo CheckCollision(const std::shared_ptr<ColliderComponent>& _collider, glm::vec3 _velocity, glm::vec3 _otherVelocity) const;

	virtual void AddForce(const glm::vec3 _force) {}

	std::shared_ptr<ColliderComponent> GetCollider() const { return m_collider; }
	bool GetSkipCollisionCheck() const { return m_skipCollisionCheck; }
	
	virtual bool GetIsDynamic() = 0;

	virtual glm::vec3 GetVelocity() { return glm::vec3(0.0f); }
	virtual float GetMass() { return 1.0f; }
	virtual float GetElasticity () { return 0.0f; }

	virtual float GetStaticFriction() { return 0.5f; }
	virtual float GetDynamicFriction() { return 0.5f; }

	void SetSkipCollisionCheck(const bool _skipCollisionCheck) { m_skipCollisionCheck = _skipCollisionCheck; }
	
	virtual void SetVelocity(const glm::vec3 _velocity) {}
};