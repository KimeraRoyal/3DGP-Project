#pragma once

#include "ICollider.h"

class SphereCollider : public ICollider
{
private:
	float m_radius;
public:
	SphereCollider();
	
	void CheckCollision(ICollider* _other) override { _other->CheckCollision(this); }
	void CheckCollision(SphereCollider* _other) override;
	void CheckCollision(PlaneCollider* _other) override;
	void CheckCollision(CubeCollider* _other) override;

	[[nodiscard]] float GetRadius() const { return m_radius; }

	void SetRadius(const float _radius) { m_radius = _radius; }
};
