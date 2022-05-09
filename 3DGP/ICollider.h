#pragma once

class Transform;

class ICollider
{
private:
	Transform* m_transform;
protected:
	[[nodiscard]] Transform* GetTransform() const { return m_transform; }

	void SetTransform(Transform* _transform) { m_transform = _transform; }
public:
	ICollider() : m_transform(nullptr) {}
	virtual ~ICollider() = default;
};