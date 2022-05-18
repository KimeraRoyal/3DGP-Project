#include "ColliderComponent.h"

#include "Scene.h"

#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "CubeCollider.h"

void ColliderComponent::Start()
{
	m_collider->SetTransform(GetTransform());
}

CollisionInfo ColliderComponent::CheckCollision(const std::shared_ptr<ColliderComponent>& _other, const glm::vec3 _velocity, const glm::vec3 _otherVelocity) const
{
	return m_collider->CheckCollision(_other->GetCollider().get(), _velocity, _otherVelocity);
}

std::shared_ptr<IComponent> ColliderComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<ColliderComponent> component = std::make_unique<ColliderComponent>();

	const std::string colliderType = _value["type"].GetString();
	if (colliderType == "sphere") // Sphere
	{
		const std::shared_ptr<SphereCollider> sphere = std::make_unique<SphereCollider>();
		sphere->SetRadius(_value["radius"].GetFloat());
		component->SetCollider(sphere);
	}
	else if (colliderType == "plane") // Plane
	{
		const std::shared_ptr<PlaneCollider> plane = std::make_unique<PlaneCollider>();
		component->SetCollider(plane);
	}
	else if (colliderType == "cube") // Cube
	{
		const std::shared_ptr<CubeCollider> cube = std::make_unique<CubeCollider>();
		component->SetCollider(cube);
	}
	else { throw std::runtime_error("Unsupported collider component type."); } // Invalid type value

	if (_value.HasMember("offset")) { component->GetCollider()->SetOffset(ParseVector3(_value["offset"])); }

	return std::static_pointer_cast<IComponent>(component);
}
