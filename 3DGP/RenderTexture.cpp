#include "RenderTexture.h"

#include <stdexcept>

RenderTexture::RenderTexture(const int _width, const int _height, const unsigned int _colorBufferCount)
{
	// Generate and bind framebuffer object.
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
		glBindTexture(GL_TEXTURE_2D, m_textureIds[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		// The render texture should not generate minmaps.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textureIds[i], 0);

		m_attachments[i] = GL_COLOR_ATTACHMENT0 + i;
	}

	// Generate and bind render buffer.
	glGenRenderbuffers(1, &m_rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
	
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	
	// Assign the render buffer to the frame buffer object.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);
	
	// Unbind framebuffer object.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_bufferCount = _colorBufferCount;
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
	glDrawBuffers(m_bufferCount, m_attachments);
}

void RenderTexture::UnbindFramebuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}