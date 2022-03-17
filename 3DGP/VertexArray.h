#pragma once

#include <gl/glew.h>

class VertexArray
{
private:
	GLuint m_vaoId;

	bool m_dirty;
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();

	inline GLuint GetId() { return m_vaoId; }
};

