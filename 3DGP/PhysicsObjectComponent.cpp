#include "PhysicsObjectComponent.h"

#include "Scene.h"
#include "GameObject.h"

#include "ColliderComponent.h"

void PhysicsObjectComponent::Start()
{
	m_collider = GetGameObject()->GetComponent<ColliderComponent>();

	GetScene()->GetPhysicsSystem()->AddPhysicsObject(std::static_pointer_cast<PhysicsObjectComponent>(shared_from_this()));
}
