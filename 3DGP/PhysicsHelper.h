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
	static CollisionInfo SphereOnSphere(SphereCollider* _a, SphereCollider* _b);
	static CollisionInfo SphereOnPlane(SphereCollider* _a, PlaneCollider* _b);
	static CollisionInfo SphereOnCube(SphereCollider* _a, CubeCollider* _b);

	static CollisionInfo CubeOnCube(CubeCollider* _a, CubeCollider* _b);
	static CollisionInfo CubeOnPlane(CubeCollider* _a, PlaneCollider* _b);
};
