#pragma once

#include <glm/vec3.hpp>

#include "IComponent.h"

class ColliderComponent;

class PhysicsObjectComponent : public IComponent
{
private:
	std::shared_ptr<ColliderComponent> m_collider;
public:
	void Start() override;

	virtual void AddForce(const glm::vec3 _force) {}

	std::shared_ptr<ColliderComponent> GetCollider() const { return m_collider; }

	virtual bool GetIsDynamic() = 0;

	virtual glm::vec3 GetVelocity() { return glm::vec3(0.0f); }
	virtual float GetMass() { return 1.0f; }
	virtual float GetElasticity () { return 1.0f; }

	virtual float GetStaticFriction() { return 0.0f; }
	virtual float GetDynamicFriction() { return 0.0f; }

	virtual void SetVelocity(const glm::vec3 _velocity) {}
};