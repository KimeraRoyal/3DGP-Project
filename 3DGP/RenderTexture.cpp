#include "RenderTexture.h"

#include <stdexcept>

RenderTexture::RenderTexture(const int _width, const int _height, const unsigned int _colorBufferCount, const Params& _params)
{
	// Generate and bind framebuffer object.
	m_fboId = 0;
	glGenFramebuffers(1, &m_fboId);
	if (!m_fboId) { throw std::runtime_error("Failed to load frame buffer object in render texture."); }
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	// Ensure the user isn't doing anything stupid.
	if (_colorBufferCount < 1) { throw std::runtime_error("Tried to generate an amount of color buffers exceeding the minimum."); }
	if (_colorBufferCount > c_maxBuffers) { throw std::runtime_error("Tried to generate an amount of color buffers exceeding the maximum."); }
	
	// Generate and bind texture.
	glGenTextures(_colorBufferCount, m_textureIds);
	for(unsigned int i = 0; i < _colorBufferCount; i++)
	{
		Params::FramebufferParams fbParams = _params.m_framebufferParams[i % _params.m_framebufferParams.size()];
		
		glBindTexture(GL_TEXTURE_2D, m_textureIds[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, fbParams.m_internalFormat, _width, _height, 0, fbParams.m_format, fbParams.m_type, nullptr);

		// The render texture should not generate minmaps.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, fbParams.m_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, fbParams.m_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, fbParams.m_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, fbParams.m_wrap);

		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, fbParams.m_startingAttachment + i, GL_TEXTURE_2D, m_textureIds[i], 0);

		m_attachments[i] = fbParams.m_startingAttachment + i;
	}
	
	m_bufferCount = _colorBufferCount;
	glDrawBuffers(m_bufferCount, m_attachments);
	
	// Generate and bind render buffer.
	m_rboId = 0;
	glGenRenderbuffers(1, &m_rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
	
	glRenderbufferStorage(GL_RENDERBUFFER, _params.m_renderBufferFormat, _width, _height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	
	// Assign the render buffer to the frame buffer object.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);
	
	// Unbind framebuffer object.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTexture::~RenderTexture()
{
	glDeleteRenderbuffers(1, &m_rboId);
	glDeleteTextures(m_bufferCount, m_textureIds);
	glDeleteFramebuffers(1, &m_fboId);
}

void RenderTexture::BindFramebuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void RenderTexture::UnbindFramebuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::BindAll() const
{
	for (unsigned int i = 0; i < m_bufferCount; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureIds[i]);
	}
}

void RenderTexture::UnbindAll() const
{
	for (unsigned int i = 0; i < m_bufferCount; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}