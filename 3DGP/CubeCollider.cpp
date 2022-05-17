#include "CubeCollider.h"

#include "PhysicsHelper.h"

CollisionInfo CubeCollider::CheckCollision(SphereCollider* _other)
{
	return PhysicsHelper::SphereOnCube(_other, this);
}

CollisionInfo CubeCollider::CheckCollision(PlaneCollider* _other)
{
	return PhysicsHelper::CubeOnPlane(this, _other);
}

CollisionInfo CubeCollider::CheckCollision(CubeCollider* _other)
{
	return PhysicsHelper::CubeOnCube(this, _other);
}