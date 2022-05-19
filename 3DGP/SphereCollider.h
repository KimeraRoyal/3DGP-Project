#pragma once

#include "ICollider.h"

class SphereCollider : public ICollider
{
private:
	float m_radius;
public:
	SphereCollider();

	std::shared_ptr<ICollider> GenerateClone() override;

	CollisionInfo CheckCollision(ICollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity) override { return _other->CheckCollision(this, _otherVelocity, _velocity); }
	CollisionInfo CheckCollision(SphereCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;
	CollisionInfo CheckCollision(PlaneCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;
	CollisionInfo CheckCollision(CubeCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;

	[[nodiscard]] float GetRadius() const { return m_radius; }

	void SetRadius(const float _radius) { m_radius = _radius; }

	glm::mat3 CalculateBodyInertia(const float _mass) override
	{
		const float radiusSquared = static_cast<float>(std::pow(m_radius, 2));
		return glm::mat3(
			2.0f / 5.0f * _mass * radiusSquared, 0, 0,
			0, 2.0f / 5.0f * _mass * radiusSquared, 0,
			0, 0, 2.0f / 5.0f * _mass * radiusSquared);
	}
};