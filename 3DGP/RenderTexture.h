#pragma once

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
	RenderTexture(int _width, int _height, unsigned int _colorBufferCount = 1);
	~RenderTexture() override;

	RenderTexture(const RenderTexture& _copy) = delete;
	RenderTexture& operator=(const RenderTexture& _other) = delete;

	void BindFramebuffer() const;
	void UnbindFramebuffer() const;

	[[nodiscard]] GLuint GetTexture(const unsigned int _index) const { return m_textureIds[_index]; }
	[[nodiscard]] GLuint GetId() override { return GetTexture(0); }
};

