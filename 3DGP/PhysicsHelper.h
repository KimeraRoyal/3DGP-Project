#pragma once

#include <glm/vec3.hpp>

#include "CollisionInfo.h"

class SphereCollider;
class PlaneCollider;
class CubeCollider;

class PhysicsHelper
{
private:
	PhysicsHelper() = default;
	
public:
	static CollisionInfo SphereOnSphere(SphereCollider* _a, SphereCollider* _b, glm::vec3 _velocity, glm::vec3 _otherVelocity);
	static CollisionInfo SphereOnPlane(SphereCollider* _a, PlaneCollider* _b, glm::vec3 _velocity, glm::vec3 _otherVelocity);
	static CollisionInfo SphereOnCube(SphereCollider* _a, CubeCollider* _b, glm::vec3 _velocity, glm::vec3 _otherVelocity);

	static CollisionInfo CubeOnCube(CubeCollider* _a, CubeCollider* _b, glm::vec3 _velocity, glm::vec3 _otherVelocity);
	static CollisionInfo CubeOnPlane(CubeCollider* _a, PlaneCollider* _b, glm::vec3 _velocity, glm::vec3 _otherVelocity);
};
