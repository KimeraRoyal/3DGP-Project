#include "SphereCollider.h"

#include "PhysicsHelper.h"

SphereCollider::SphereCollider()
{
	m_radius = 0.0f;
}

CollisionInfo SphereCollider::CheckCollision(SphereCollider* _other)
{
	return PhysicsHelper::SphereOnSphere(this, _other);
}

CollisionInfo SphereCollider::CheckCollision(PlaneCollider* _other)
{
	return {};
}

CollisionInfo SphereCollider::CheckCollision(CubeCollider* _other)
{
	return {};
}
