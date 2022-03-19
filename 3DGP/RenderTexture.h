#pragma once

#include <GL/glew.h>

class RenderTexture
{
private:
	GLuint m_fboId;
	GLuint m_textureId;
	GLuint m_rboId;
public:
	RenderTexture(int _width, int _height);
	~RenderTexture();

	RenderTexture(const RenderTexture& _copy) = delete;
	RenderTexture& operator=(const RenderTexture& _other) = delete;

	GLuint GetTexture() const { return m_textureId; }
};

