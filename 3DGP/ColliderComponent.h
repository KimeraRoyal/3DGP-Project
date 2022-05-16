#pragma once

#include "IComponent.h"
#include "IJsonParser.h"

class ICollider;
class Resources;

class ColliderComponent : public IComponent
{
private:
	std::shared_ptr<ICollider> m_collider;
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	void Start() override;

	std::shared_ptr<ICollider> GetCollider() const { return m_collider; }

	void SetCollider(const std::shared_ptr<ICollider>& _collider) { m_collider = _collider; }
};

