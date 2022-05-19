#pragma once

#include "ILight.h"

class DirectionalLight final : public ILight
{
private:
	static size_t s_directionKey;
	
	static size_t s_ambientKey;
	static size_t s_diffuseKey;
	static size_t s_specularKey;
public:
	DirectionalLight() : ILight() {}
	~DirectionalLight() override = default;

	std::shared_ptr<ILight> GenerateClone() override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) override;
};

