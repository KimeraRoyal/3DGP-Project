#pragma once

#include "ILight.h"

class AmbientLight final : public ILight
{
private:
	static size_t s_ambientKey;
public:
	AmbientLight() : ILight() {}
	~AmbientLight() override = default;

	std::shared_ptr<ILight> GenerateClone() override;

	void AssignUniforms(const std::shared_ptr<ShaderProgram>&_program) override;
};