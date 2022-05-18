#include "PlaneCollider.h"

#include "PhysicsHelper.h"

#include "Transform.h"

PlaneCollider::PlaneCollider()
{
	m_size = glm::vec2(1.0f);
}

CollisionInfo PlaneCollider::CheckCollision(SphereCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return ReverseCollision(PhysicsHelper::SphereOnPlane(_other, this, _otherVelocity, _velocity));
}

CollisionInfo PlaneCollider::CheckCollision(CubeCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return ReverseCollision(PhysicsHelper::CubeOnPlane(_other, this, _otherVelocity, _velocity));
}

glm::vec3 PlaneCollider::GetNormal() const
{
	return GetTransform()->GetUp();
}