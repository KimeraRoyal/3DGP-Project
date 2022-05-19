#pragma once

#include <glm/mat3x3.hpp>

#include "CollisionInfo.h"

class Transform;

class SphereCollider;
class PlaneCollider;
class CubeCollider;

class ICollider
{
private:
	Transform* m_transform;

	glm::vec3 m_offset;
	
protected:
	friend class ColliderComponent;
	
	void SetTransform(Transform* _transform) { m_transform = _transform; }
	
	void SetOffset(const glm::vec3 _offset) { m_offset = _offset; }

	static CollisionInfo ReverseCollision(CollisionInfo _collision)
	{
		_collision.SetCollisionNormal(-_collision.GetCollisionNormal());
		_collision.SetDifference(-_collision.GetDifference());

		const glm::vec3 aClipPoint = _collision.GetAClipPoint();
		_collision.SetAClipPoint(_collision.GetBClipPoint());
		_collision.SetBClipPoint(aClipPoint);
		
		return _collision;
	}
	
public:
	ICollider() : m_transform(nullptr), m_offset(glm::vec3(0.0f)) {}
	virtual ~ICollider() = default;

	// Child classes use double dispatch to eliminate the need to know what kind of collider is being checked.
	virtual CollisionInfo CheckCollision(ICollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) = 0;
	virtual CollisionInfo CheckCollision(SphereCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) = 0;
	virtual CollisionInfo CheckCollision(PlaneCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) = 0;
	virtual CollisionInfo CheckCollision(CubeCollider* _other, glm::vec3 _velocity, glm::vec3 _otherVelocity) = 0;

	[[nodiscard]] Transform* GetTransform() const { return m_transform; }

	[[nodiscard]] glm::vec3 GetOffset() const { return m_offset; }
	[[nodiscard]] glm::vec3 GetPosition() const;

	virtual glm::mat3 CalculateBodyInertia(float _mass) = 0;
};