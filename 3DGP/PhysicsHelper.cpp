#include "PhysicsHelper.h"

#include <stdexcept>

#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "CubeCollider.h"

#include "Transform.h"

CollisionInfo PhysicsHelper::SphereOnSphere(SphereCollider* _a, SphereCollider* _b, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	CollisionInfo collision;

	// Calculate distance of colliding objects from each other
	const glm::vec3 aPos = _a->GetPosition(), bPos = _b->GetPosition();
	collision.SetDifference(aPos - bPos);
	collision.SetCollisionNormal(glm::normalize(collision.GetDifference()));
	collision.SetDistance(glm::length(collision.GetDifference()));

	// Calculate whether collision has happened
	const float aRadius = _a->GetRadius(), bRadius = _b->GetRadius();
	const float radiusSum = aRadius + bRadius;
	collision.SetHasCollision(collision.GetDistance() <= radiusSum);

	// Calculate the position of the collision (will be the midpoint of overlapping masses if distance < radiusSum)
	if(collision.GetHasCollision())
	{
		collision.SetCollisionPoint(aPos + (bPos - aPos) * aRadius / (aRadius + bRadius));

		collision.SetAClipPoint(glm::normalize(collision.GetCollisionPoint() - aPos) * aRadius + aPos);
		collision.SetBClipPoint(glm::normalize(collision.GetCollisionPoint() - bPos) * bRadius + bPos);
	}

	return collision;
}

//TODO: Plane bounds check
CollisionInfo PhysicsHelper::SphereOnPlane(SphereCollider* _a, PlaneCollider* _b, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	CollisionInfo collision;

	// Calculate distance of colliding objects from each other
	const glm::vec3 aPos = _a->GetPosition(), bPos = _b->GetPosition();
	collision.SetDifference(aPos - bPos); //Returning 0,0
	collision.SetDistance(abs(glm::dot(collision.GetDifference(), _b->GetNormal())));
	collision.SetCollisionNormal(_b->GetNormal());

	// Calculate whether collision has happened
	collision.SetCollisionPoint(-collision.GetCollisionNormal() * collision.GetDistance() + aPos);
	collision.SetAClipPoint(-collision.GetCollisionNormal() * _a->GetRadius() + aPos);
	collision.SetBClipPoint(-collision.GetCollisionPoint());

	const bool xCheck = collision.GetAClipPoint().x <= bPos.x + _b->GetSize().x && collision.GetAClipPoint().x >= bPos.x - _b->GetSize().x;
	const bool zCheck = collision.GetAClipPoint().z <= bPos.z + _b->GetSize().y && collision.GetAClipPoint().z >= bPos.z - _b->GetSize().y;
	collision.SetHasCollision(collision.GetDistance() <= _a->GetRadius() && xCheck && zCheck);

	return collision;
}

CollisionInfo PhysicsHelper::SphereOnCube(SphereCollider* _a, CubeCollider* _b, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	CollisionInfo collision;
	throw std::runtime_error("Sphere v Cube collision is not implemented.");
	return collision;
}

CollisionInfo PhysicsHelper::CubeOnCube(CubeCollider* _a, CubeCollider* _b, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	CollisionInfo collision;
	throw std::runtime_error("Cube v Cube collision is not implemented.");
	return collision;
}

CollisionInfo PhysicsHelper::CubeOnPlane(CubeCollider* _a, PlaneCollider* _b, const glm::vec3 _velocity, const glm::vec3 _otherVelocity)
{
	CollisionInfo collision;
	throw std::runtime_error("Cube v Plane collision is not implemented.");
	return collision;
}
