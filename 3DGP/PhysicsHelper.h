#pragma once

#include <glm/vec3.hpp>

#include "CollisionInfo.h"

class SphereCollider;

class PhysicsHelper
{
private:
	PhysicsHelper() = default;
	
public:
	static CollisionInfo SphereOnSphere(SphereCollider* _a, SphereCollider* _b);
};
