#pragma once

#include <glm/ext/matrix_transform.hpp>

#include "ICollider.h"

class CubeCollider : public ICollider
{
public:
	CollisionInfo CheckCollision(ICollider* _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity) override { return _other->CheckCollision(this, _otherVelocity, _velocity); }
	CollisionInfo CheckCollision(SphereCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;
	CollisionInfo CheckCollision(PlaneCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;
	CollisionInfo CheckCollision(CubeCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) override;

	glm::mat3 CalculateBodyInertia(float _mass) override
	{
		return glm::identity<glm::mat3>();
	}
};
