#pragma once

#include "IModel.h"
#include "ShaderProgram.h"
#include "RenderTexture.h"

#include "FXAA.h"

class Screen
{
private:
	static size_t s_projectionKey;
	static size_t s_modelKey;
	static size_t s_texelStepKey;
	
	std::shared_ptr<IModel> m_screenQuad;

	std::shared_ptr<ShaderProgram> m_program;

	std::shared_ptr<RenderTexture> m_renderTexture;

	FXAA m_fxaa;
public:
	Screen(const std::shared_ptr<ShaderProgram>& _shaderProgram, unsigned int _colorBufferCount = 1);

	void Bind() const { m_renderTexture->BindFramebuffer(); }
	void Unbind() const { m_renderTexture->UnbindFramebuffer(); }

	void Draw() const;

	[[nodiscard]] FXAA& GetFxaa() { return m_fxaa; }
};
