#pragma once

#include "ICollider.h"

class CubeCollider : public ICollider
{
public:
	CollisionInfo CheckCollision(ICollider* _other) override { return _other->CheckCollision(this); }
	CollisionInfo CheckCollision(SphereCollider* _other) override;
	CollisionInfo CheckCollision(PlaneCollider* _other) override;
	CollisionInfo CheckCollision(CubeCollider* _other) override;
};

