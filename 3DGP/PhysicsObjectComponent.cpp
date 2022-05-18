#include "PhysicsObjectComponent.h"

#include "Scene.h"
#include "GameObject.h"

#include "ColliderComponent.h"

void PhysicsObjectComponent::Start()
{
	m_collider = GetGameObject()->GetComponent<ColliderComponent>();

	GetScene()->GetPhysicsSystem()->AddPhysicsObject(std::static_pointer_cast<PhysicsObjectComponent>(shared_from_this()));
}

CollisionInfo PhysicsObjectComponent::CheckCollision(const std::shared_ptr<ColliderComponent>& _collider, const glm::vec3 _velocity, const glm::vec3 _otherVelocity) const
{
	if (_collider == m_collider) { return {}; }
	return m_collider->CheckCollision(_collider, _velocity, _otherVelocity);
}

void PhysicsObjectComponent::FixedUpdate(float _deltaTime)
{
	m_skipCollisionCheck = false;
}
