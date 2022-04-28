#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/vec2.hpp>

#include "ITexture.h"

#include "ColorBuffer.h"

class RenderTexture : public ITexture
{
private:
	glm::ivec2 m_size;
	
	GLuint m_fboId;
	GLuint m_rboId;

	std::vector<ColorBuffer> m_colorBuffers;
	
	GLuint m_startingAttachment;
	
	GLuint m_renderBufferFormat;
	GLuint m_renderBufferAttachment;

	bool m_dirty;

	void GenerateBuffers();
public:
	RenderTexture(int _width, int _height);
	~RenderTexture() override;

	void BindFramebuffer();
	void UnbindFramebuffer() const;

	void BindAll(GLuint _programId);
	void UnbindAll() const;

	void AddColorBuffer(GLenum _internalFormat = GL_RGB, GLenum _format = GL_RGB, GLenum _type = GL_UNSIGNED_BYTE, GLenum _filter = GL_LINEAR, GLenum _wrap = GL_CLAMP_TO_EDGE);
	void AddColorBuffers(unsigned int _count, GLenum _internalFormat = GL_RGB, GLenum _format = GL_RGB, GLenum _type = GL_UNSIGNED_BYTE, GLenum _filter = GL_LINEAR, GLenum _wrap = GL_CLAMP_TO_EDGE);

	[[nodiscard]] GLuint GetTexture(const unsigned int _index) const { return m_colorBuffers[_index].GetTextureId(); }
	[[nodiscard]] GLuint GetId() override { return GetTexture(0); }

	void SetStartingAttachment(const GLuint _startingAttachment)
	{
		m_startingAttachment = _startingAttachment;

		m_dirty = true;
	}

	void SetRenderbuffer(const GLuint _format, const GLuint _attachment)
	{
		m_renderBufferFormat = _format;
		m_renderBufferAttachment = _attachment;

		m_dirty = true;
	}
};

