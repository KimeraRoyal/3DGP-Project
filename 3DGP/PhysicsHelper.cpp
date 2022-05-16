#include "PhysicsHelper.h"

#include "SphereCollider.h"
#include "Transform.h"

CollisionInfo PhysicsHelper::SphereOnSphere(SphereCollider* _a, SphereCollider* _b)
{
	CollisionInfo collision;

	// Calculate distance of colliding objects from each other
	const glm::vec3 aPos = _a->GetPosition(), bPos = _b->GetPosition();
	collision.SetDifference(aPos - bPos);
	collision.SetDistance(glm::length(collision.GetDifference()));

	// Calculate whether collision has happened
	const float aRadius = _a->GetRadius(), bRadius = _b->GetRadius();
	const float radiusSum = aRadius + bRadius;
	collision.SetHasCollision(collision.GetDistance() <= radiusSum);

	// Calculate the position of the collision (will be the midpoint of overlapping masses if distance < radiusSum)
	if(collision.GetHasCollision()) { collision.SetCollisionPoint(aPos + (bPos - aPos) * aRadius / (aRadius + bRadius)); }

	return collision;
}
