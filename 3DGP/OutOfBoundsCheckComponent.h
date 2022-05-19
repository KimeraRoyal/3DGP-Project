#pragma once

#include "IComponent.h"
#include "IJsonParser.h"

class RigidbodyComponent;

class OutOfBoundsCheckComponent : public IComponent
{
private:
	float m_minHeight;

	glm::vec3 m_minResetPosition;
	glm::vec3 m_maxResetPosition;

	std::shared_ptr<RigidbodyComponent> m_rigidbody;

	void SetMinHeight(const float _minHeight) { m_minHeight = _minHeight; }
	void SetResetPosition(const glm::vec3 _resetPosition)
	{
		m_minResetPosition = _resetPosition;
		m_maxResetPosition = _resetPosition;
	}

	void SetMinResetPosition(const glm::vec3 _minResetPosition) { m_minResetPosition = _minResetPosition; }
	void SetMaxResetPosition(const glm::vec3 _maxResetPosition) { m_maxResetPosition = _maxResetPosition; }

public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};

	void Start() override;

	void Update(Time& _time, Input& _input) override;

	std::shared_ptr<IComponent> GenerateClone() override;
};

