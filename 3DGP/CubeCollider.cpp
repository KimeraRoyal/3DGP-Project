#include "CubeCollider.h"

#include "PhysicsHelper.h"

std::shared_ptr<ICollider> CubeCollider::GenerateClone()
{
	std::shared_ptr<CubeCollider> clone = std::make_shared<CubeCollider>();
	return clone;
}

CollisionInfo CubeCollider::CheckCollision(SphereCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return ReverseCollision(PhysicsHelper::SphereOnCube(_other, this, _otherVelocity, _velocity));
}

CollisionInfo CubeCollider::CheckCollision(PlaneCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::CubeOnPlane(this, _other, _velocity, _otherVelocity);
}

CollisionInfo CubeCollider::CheckCollision(CubeCollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	return PhysicsHelper::CubeOnCube(this, _other, _velocity, _otherVelocity);
}