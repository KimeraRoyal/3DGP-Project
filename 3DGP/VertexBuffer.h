#pragma once

#include <gl/glew.h>

class VertexBuffer
{
private:
	GLuint m_vboId;

	bool m_dirty;
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void Unbind();

	inline GLuint GetId() { return m_vboId; }
};

