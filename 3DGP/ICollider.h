#pragma once

class Transform;

class SphereCollider;
class PlaneCollider;
class CubeCollider;

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

	virtual void CheckCollision(ICollider* _other) = 0;
	virtual void CheckCollision(SphereCollider* _other) = 0;
	virtual void CheckCollision(PlaneCollider* _other) = 0;
	virtual void CheckCollision(CubeCollider* _other) = 0;
};