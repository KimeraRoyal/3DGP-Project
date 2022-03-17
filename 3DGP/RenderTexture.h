#pragma once

#include <gl/glew.h>

class RenderTexture
{
private:
	GLuint m_fboId;
	GLuint m_textureId;
	GLuint m_rboId;

	RenderTexture(const RenderTexture& _copy) = delete;
	RenderTexture& operator=(const RenderTexture& _other) = delete;
public:
	RenderTexture(int _width, int _height);
	~RenderTexture();

	void Bind();
	void Unbind();

	inline GLuint GetTexture() { return m_textureId; }
};

