#pragma once

#include "IComponent.h"

#include "ShaderProgram.h"

class RenderableComponent : public IComponent
{
public:
	void Start() override;
	virtual void Draw() = 0;

	virtual std::shared_ptr<ShaderProgram> GetProgram() = 0;
};