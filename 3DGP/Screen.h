#pragma once

#include <memory>
#include <string>

#include "IModel.h"
#include "ShaderProgram.h"
#include "RenderTexture.h"

class Screen
{
private:
	std::shared_ptr<IModel> m_screenQuad;

	std::shared_ptr<ShaderProgram> m_program;

	std::shared_ptr<RenderTexture> m_renderTexture;

	GLint m_projectionLoc;
	GLint m_modelLoc;
public:
	Screen(const std::string& _vertShader, const std::string& _fragShader, unsigned int _colorBufferCount = 1);

	void Bind() const { m_renderTexture->Bind(); }
	void Unbind() const { m_renderTexture->Unbind(); }

	void Draw() const;
};
