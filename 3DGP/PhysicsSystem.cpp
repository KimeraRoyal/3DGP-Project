#include "PhysicsSystem.h"

#include "GameObject.h"
#include "RigidbodyComponent.h"

#include "Time.h"

void PhysicsSystem::Update(Time& _time, const std::vector<std::shared_ptr<GameObject>>& _gameObjects)
{
	m_fixedTimer += _time.GetDeltaTime();

	while(m_fixedTimer >= m_timestep)
	{
		for (const std::shared_ptr<GameObject>& gameObject : _gameObjects)
		{
			gameObject->FixedUpdate(m_timestep);
		}
		
		PhysicsStep();
		
		m_fixedTimer -= m_timestep;
	}
}

void PhysicsSystem::PhysicsStep()
{
	for (const std::shared_ptr<RigidbodyComponent>& rigidbody : m_rigidbodies)
	{
		rigidbody->AddForce(m_gravity);

		ResolveCollisions(rigidbody);

		rigidbody->PhysicsStep(m_timestep);

		rigidbody->ClearForce();
		rigidbody->ClearTorque();
	}
}

void PhysicsSystem::ResolveCollisions(const std::shared_ptr<RigidbodyComponent>& _rigidbody)
{
	for (const std::shared_ptr<PhysicsObjectComponent>& physicsObject : m_physicsObjects)
	{
		if (_rigidbody == physicsObject) { continue; }

		CollisionInfo collision = _rigidbody->CheckCollision(physicsObject->GetCollider());
		if (!collision.GetHasCollision()) { continue; }
		ResolveCollision(_rigidbody, physicsObject, collision);
	}
}

void PhysicsSystem::ResolveCollision(const std::shared_ptr<PhysicsObjectComponent>& _a, const std::shared_ptr<PhysicsObjectComponent>& _b, const CollisionInfo& _collision) const
{
	// Initial values
	const glm::vec3 collisionNormal = glm::normalize(_collision.GetDifference());

	glm::vec3 aVelocity = _a->GetVelocity(), bVelocity = _b->GetVelocity();
	glm::vec3 velocityDiff = bVelocity - aVelocity;
	float negativeSpeed = glm::dot(velocityDiff, collisionNormal);
	if (negativeSpeed >= 0) { return; }

	const float aMass = _a->GetMass(), bMass = _b->GetMass();

	// Impulse
	const float combinedElasticity = _a->GetElasticity() * _b->GetElasticity();
	const float impulseStrength = -(1.0f + combinedElasticity) * negativeSpeed / (aMass + bMass);
	const glm::vec3 impulse = impulseStrength * collisionNormal;

	if (_a->GetIsDynamic()) { aVelocity -= impulse * aMass; }
	if (_b->GetIsDynamic()) { bVelocity += impulse * bMass; }

	// Apply friction
	velocityDiff = bVelocity - aVelocity;
	negativeSpeed = glm::dot(velocityDiff, collisionNormal);

	const glm::vec3 tangent = glm::normalize(velocityDiff - negativeSpeed * collisionNormal);
	const float frictionVelocity = glm::dot(velocityDiff, tangent);

	const float aStaticFriction = _a->GetStaticFriction(), bStaticFriction = _b->GetStaticFriction();
	const float aDynamicFriction = _a->GetDynamicFriction(), bDynamicFriction = _b->GetDynamicFriction();
	float mu = glm::length(glm::vec2(aStaticFriction, bStaticFriction));

	const float f = -frictionVelocity / (aMass + bMass);

	glm::vec3 friction;
	if (abs(f) < impulseStrength * mu) { friction = f * tangent; }
	else
	{
		mu = glm::length(glm::vec2(aDynamicFriction, bDynamicFriction));
		friction = -impulseStrength * tangent * mu;
	}

	if (_a->GetIsDynamic()) { _a->SetVelocity(aVelocity - friction * aMass); }
	if (_b->GetIsDynamic()) { _b->SetVelocity(bVelocity + friction * bMass); }
}
