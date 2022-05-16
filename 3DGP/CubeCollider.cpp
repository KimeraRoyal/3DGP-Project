#include "CubeCollider.h"

CollisionInfo CubeCollider::CheckCollision(SphereCollider* _other)
{
	return {};
}

CollisionInfo CubeCollider::CheckCollision(PlaneCollider* _other)
{
	return {};
}

CollisionInfo CubeCollider::CheckCollision(CubeCollider* _other)
{
	return {};
}