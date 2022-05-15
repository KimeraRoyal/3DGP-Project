#pragma once

#include "ICollider.h"

class PlaneCollider : public ICollider
{
public:
	void CheckCollision(ICollider* _other) override { _other->CheckCollision(this); }
	void CheckCollision(SphereCollider* _other) override;
	void CheckCollision(PlaneCollider* _other) override {} // No Plane v Plane
	void CheckCollision(CubeCollider* _other) override;
};

