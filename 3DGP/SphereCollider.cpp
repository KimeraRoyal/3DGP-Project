#include "SphereCollider.h"

#include "PhysicsHelper.h"

SphereCollider::SphereCollider()
{
	m_radius = 0.0f;
}

std::shared_ptr<ICollider> SphereCollider::GenerateClone()
{
	std::shared_ptr<SphereCollider> clone = std::make_shared<SphereCollider>();
	clone->SetOffset(GetOffset());
	clone->m_radius = m_radius;
	return clone;
}

CollisionInfo SphereCollider::CheckCollision(SphereCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::SphereOnSphere(this, _other, _velocity, _otherVelocity);
}

CollisionInfo SphereCollider::CheckCollision(PlaneCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::SphereOnPlane(this, _other, _velocity, _otherVelocity);
}

CollisionInfo SphereCollider::CheckCollision(CubeCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::SphereOnCube(this, _other, _velocity, _otherVelocity);
}
