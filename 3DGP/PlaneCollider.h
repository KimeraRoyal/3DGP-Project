#pragma once

#include <glm/vec2.hpp>

#include "ICollider.h"

class PlaneCollider : public ICollider
{
private:
	glm::vec2 m_size;
public:
	PlaneCollider();
	
	CollisionInfo CheckCollision(ICollider* _other) override { return _other->CheckCollision(this); }
	CollisionInfo CheckCollision(SphereCollider* _other) override;
	CollisionInfo CheckCollision(PlaneCollider* _other) override { return {}; } // No Plane v Plane
	CollisionInfo CheckCollision(CubeCollider* _other) override;

	[[nodiscard]] glm::vec2 GetSize() const { return m_size; }

	[[nodiscard]] glm::vec3 GetNormal() const;

	void SetSize(const glm::vec2 _size) { m_size = _size; }
};

