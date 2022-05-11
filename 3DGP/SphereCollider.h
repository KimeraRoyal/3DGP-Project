#pragma once

#include "ICollider.h"
#include "ColliderType.h"

class SphereCollider : public ICollider
{
private:
	float m_radius;
public:
	SphereCollider();

	float GetRadius() const { return m_radius; }

	ColliderType GetColliderType() override { return ColliderType::Sphere; }

	void SetRadius(const float _radius) { m_radius = _radius; }
};
