#pragma once

#include "ShaderProgram.h"

class IRenderable
{
public:
	virtual ~IRenderable() = default;
	
	virtual void Draw() = 0;

	virtual std::shared_ptr<ShaderProgram> GetProgram() = 0;
};