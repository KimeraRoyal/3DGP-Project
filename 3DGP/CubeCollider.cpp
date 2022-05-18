#include "CubeCollider.h"

#include "PhysicsHelper.h"

CollisionInfo CubeCollider::CheckCollision(SphereCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::SphereOnCube(_other, this);
}

CollisionInfo CubeCollider::CheckCollision(PlaneCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::CubeOnPlane(this, _other, _velocity, _otherVelocity);
}

CollisionInfo CubeCollider::CheckCollision(CubeCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::CubeOnCube(this, _other, _velocity, _otherVelocity);
}