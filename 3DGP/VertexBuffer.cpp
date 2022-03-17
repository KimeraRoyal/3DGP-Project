#include "VertexBuffer.h"

#include <stdexcept>

VertexBuffer::VertexBuffer()
{
	// Generate new vertex buffer object.
	m_vboId = 0;
	glGenBuffers(1, &m_vboId);
	if (!m_vboId)
	{
		throw std::runtime_error("Failed to generate vertex buffer.");
	}

	m_dirty = false;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vboId);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}