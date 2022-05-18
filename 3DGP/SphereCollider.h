#pragma once

#include "ICollider.h"

class SphereCollider : public ICollider
{
private:
	float m_radius;
public:
	SphereCollider();
	
	CollisionInfo CheckCollision(ICollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity) override { return _other->CheckCollision(this, _otherVelocity, _velocity); }
	CollisionInfo CheckCollision(SphereCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;
	CollisionInfo CheckCollision(PlaneCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;
	CollisionInfo CheckCollision(CubeCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;

	[[nodiscard]] float GetRadius() const { return m_radius; }

	void SetRadius(const float _radius) { m_radius = _radius; }
};
