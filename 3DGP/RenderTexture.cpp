#include "RenderTexture.h"

#include <stdexcept>

RenderTexture::RenderTexture(int _width, int _height)
{
	// Generate and bind framebuffer object.
	glGenFramebuffers(1, &m_fboId);
	if (!m_fboId) { throw std::runtime_error("Failed to load Frame Buffer Object in Render Texture."); }
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	// Generate and bind texture.
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	// The render texture should not generate minmaps.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

	// Generate and bind render buffer.
	glGenRenderbuffers(1, &m_rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
	
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	
	// Assign the render buffer to the frame buffer object.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);
	
	// Unbind framebuffer object.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTexture::~RenderTexture()
{
	glDeleteRenderbuffers(1, &m_rboId);
	glDeleteTextures(1, &m_textureId);
	glDeleteFramebuffers(1, &m_fboId);
}

void RenderTexture::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void RenderTexture::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}