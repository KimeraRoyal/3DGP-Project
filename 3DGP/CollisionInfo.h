#pragma once

#include <glm/vec3.hpp>

struct CollisionInfo
{
private:
	friend class PhysicsHelper;
	
	bool m_hasCollision;

	float m_distance;
	glm::vec3 m_difference;
	glm::vec3 m_collisionNormal;
	glm::vec3 m_collisionPoint;

	void SetHasCollision(const bool _hasCollision) { m_hasCollision = _hasCollision; }
	
	void SetDistance(const float _distance) { m_distance = _distance; }
	void SetDifference(const glm::vec3 _positionDifference) { m_difference = _positionDifference; }
	void SetCollisionPoint(const glm::vec3 _collisionPoint) { m_collisionPoint = _collisionPoint; }
	void SetCollisionNormal(const glm::vec3 _collisionNormal) { m_collisionNormal = _collisionNormal; }
public:
	CollisionInfo() : m_hasCollision(false), m_distance(0.0f), m_difference(glm::vec3(0.0f)), m_collisionPoint(glm::vec3(0.0f)), m_collisionNormal(glm::vec3(0.0f)) {}
	
	[[nodiscard]] bool GetHasCollision() const { return m_hasCollision; }
	
	[[nodiscard]] float GetDistance() const { return m_distance; }
	[[nodiscard]] glm::vec3 GetDifference() const { return m_difference; }
	[[nodiscard]] glm::vec3 GetCollisionPoint() const { return m_collisionPoint; }
	[[nodiscard]] glm::vec3 GetCollisionNormal() const { return m_collisionNormal; }
};
