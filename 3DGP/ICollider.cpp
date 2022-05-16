#include "ICollider.h"

#include "Transform.h"

glm::vec3 ICollider::GetPosition() const
{
	return m_transform->GetPosition() + m_offset;
}
