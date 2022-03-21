#pragma once

#include <GL/glew.h>

class RenderTexture
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
	~RenderTexture();

	RenderTexture(const RenderTexture& _copy) = delete;
	RenderTexture& operator=(const RenderTexture& _other) = delete;

	void Bind() const;
	void Unbind() const;

	[[nodiscard]] GLuint GetTexture(const unsigned int _index) const { return m_textureIds[_index]; }
};

