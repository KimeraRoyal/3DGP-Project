#include "PhysicsSystem.h"

#include "GameObject.h"
#include "RigidbodyComponent.h"

#include "Time.h"

void PhysicsSystem::Update(Time& _time, const std::vector<std::shared_ptr<GameObject>>& _gameObjects)
{
	m_fixedTimer += _time.GetDeltaTime();

	while(m_fixedTimer >= m_timestep)
	{
		for(const std::shared_ptr<GameObject>& gameObject : _gameObjects)
		{
			gameObject->FixedUpdate(m_timestep);
		}
		
		for(const std::shared_ptr<RigidbodyComponent>& rigidbody : m_rigidbodies)
		{
			rigidbody->AddForce(m_gravity);
			
			rigidbody->PhysicsStep(m_timestep);
			
			rigidbody->ClearForce();
			rigidbody->ClearTorque();
		}
		
		m_fixedTimer -= m_timestep;
	}
}
