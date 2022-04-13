#pragma once

#include <vector>
#include <GL/glew.h>

#include "ITexture.h"

class RenderTexture : public ITexture
{
private:
	static constexpr unsigned int c_maxBuffers = 4;
	
	GLuint m_fboId;
	GLuint m_textureIds[c_maxBuffers];
	GLuint m_rboId;

	unsigned int m_attachments[c_maxBuffers];

	unsigned int m_bufferCount;
public:
	struct Params
	{
		struct FramebufferParams
		{
			GLenum m_internalFormat;
			GLenum m_format;
			GLenum m_type;

			GLuint m_startingAttachment;

			GLenum m_filter;
			GLenum m_wrap;
		};

		std::vector<FramebufferParams> m_framebufferParams;
		
		GLuint m_renderBufferFormat;
		GLuint m_renderBufferAttachment;
	};
	
	RenderTexture(int _width, int _height, unsigned int _colorBufferCount = 1, const Params& _params = { {{GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0, GL_LINEAR, GL_CLAMP_TO_EDGE} }, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT });
	~RenderTexture() override;

	void BindFramebuffer() const;
	void UnbindFramebuffer() const;

	void BindAll() const;
	void UnbindAll() const;

	[[nodiscard]] GLuint GetTexture(const unsigned int _index) const { return m_textureIds[_index]; }
	[[nodiscard]] GLuint GetId() override { return GetTexture(0); }
};

