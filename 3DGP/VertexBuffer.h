#pragma once

#include <GL/glew.h>

class VertexBuffer
{
private:
	GLuint m_vboId;

	bool m_dirty;
public:
	VertexBuffer();
	~VertexBuffer();

	VertexBuffer(const VertexBuffer& _copy) = delete;
	VertexBuffer& operator=(const VertexBuffer& _other) = delete;

	void Bind() const;
	void Unbind() const;

	GLuint GetId() const { return m_vboId; }
};

