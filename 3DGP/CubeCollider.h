#pragma once

#include "ICollider.h"

class CubeCollider : public ICollider
{
public:
	void CheckCollision(ICollider* _other) override { _other->CheckCollision(this); }
	void CheckCollision(SphereCollider* _other) override;
	void CheckCollision(PlaneCollider* _other) override;
	void CheckCollision(CubeCollider* _other) override;
};

