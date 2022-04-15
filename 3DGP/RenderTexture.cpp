#include "RenderTexture.h"

#include <stdexcept>

RenderTexture::RenderTexture(const int _width, const int _height)
{
	m_fboId = 0;
	m_rboId = 0;

	m_size = glm::ivec2(_width, _height);
	
	m_startingAttachment = GL_COLOR_ATTACHMENT0;
	
	m_renderBufferFormat = GL_DEPTH24_STENCIL8;
	m_renderBufferAttachment = GL_DEPTH_STENCIL_ATTACHMENT;

	m_dirty = false;
}

RenderTexture::~RenderTexture()
{
	glDeleteRenderbuffers(1, &m_rboId);
	for (auto& colorBuffer : m_colorBuffers)
	{
		const GLuint textureId = colorBuffer.GetTextureId();
		glDeleteTextures(1, &textureId);
	}
	glDeleteFramebuffers(1, &m_fboId);
}

void RenderTexture::BindFramebuffer()
{
	GenerateBuffers();
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void RenderTexture::UnbindFramebuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::BindAll()
{
	GenerateBuffers();
	for (unsigned int i = 0; i < m_colorBuffers.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_colorBuffers[i].GetTextureId());
	}
}

void RenderTexture::UnbindAll() const
{
	for (unsigned int i = 0; i < m_colorBuffers.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void RenderTexture::AddColorBuffer(const GLenum _internalFormat, const GLenum _format, const GLenum _type, const GLenum _filter, const GLenum _wrap)
{
	m_colorBuffers.emplace_back(ColorBuffer(_internalFormat, _format, _type, _filter, _wrap));
	m_dirty = true;
}

void RenderTexture::AddColorBuffers(const unsigned int _count, const GLenum _internalFormat, const GLenum _format, const GLenum _type, const GLenum _filter, const GLenum _wrap)
{
	for(unsigned int i = 0; i < _count; i++)
	{
		AddColorBuffer(_internalFormat, _format, _type, _filter, _wrap);
	}
}

void RenderTexture::GenerateBuffers()
{
	if (!m_dirty) { return; }
	
	// Generate and bind framebuffer object.
	glGenFramebuffers(1, &m_fboId);
	if (!m_fboId) { throw std::runtime_error("Failed to load frame buffer object in render texture."); }
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	// Generate and bind texture.
	std::vector<GLuint> textureIds;
	textureIds.resize(m_colorBuffers.size());
	glGenTextures(m_colorBuffers.size(), textureIds.data());

	std::vector<unsigned int> attachments;
	for (unsigned int i = 0; i < m_colorBuffers.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textureIds[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, m_colorBuffers[i].GetInternalFormat(), m_size.x, m_size.y, 0, m_colorBuffers[i].GetFormat(), m_colorBuffers[i].GetType(), nullptr);

		// The render texture should not generate minmaps.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_colorBuffers[i].GetFilter());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_colorBuffers[i].GetFilter());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_colorBuffers[i].GetWrap());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_colorBuffers[i].GetWrap());

		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, m_startingAttachment + i, GL_TEXTURE_2D, textureIds[i], 0);

		// Assign persistent values.
		m_colorBuffers[i].SetTextureId(textureIds[i]);
		attachments.push_back(m_startingAttachment + i);
	}

	glDrawBuffers(m_colorBuffers.size(), attachments.data());

	// Generate and bind render buffer.
	m_rboId = 0;
	glGenRenderbuffers(1, &m_rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);

	glRenderbufferStorage(GL_RENDERBUFFER, m_renderBufferFormat, m_size.x, m_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Assign the render buffer to the frame buffer object.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, m_renderBufferAttachment, GL_RENDERBUFFER, m_rboId);

	// Unbind framebuffer object.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_dirty = false;
}
