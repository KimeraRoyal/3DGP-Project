#pragma once

#include "ICollider.h"

class SphereCollider : public ICollider
{
private:
	float m_radius;
public:
	SphereCollider();
	
	CollisionInfo CheckCollision(ICollider* _other) override { return _other->CheckCollision(this); }
	CollisionInfo CheckCollision(SphereCollider* _other) override;
	CollisionInfo CheckCollision(PlaneCollider* _other) override;
	CollisionInfo CheckCollision(CubeCollider* _other) override;

	[[nodiscard]] float GetRadius() const { return m_radius; }

	void SetRadius(const float _radius) { m_radius = _radius; }
};
