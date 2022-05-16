#pragma once

#include "ICollider.h"

class PlaneCollider : public ICollider
{
public:
	CollisionInfo CheckCollision(ICollider* _other) override { return _other->CheckCollision(this); }
	CollisionInfo CheckCollision(SphereCollider* _other) override;
	CollisionInfo CheckCollision(PlaneCollider* _other) override { return {}; } // No Plane v Plane
	CollisionInfo CheckCollision(CubeCollider* _other) override;
};

