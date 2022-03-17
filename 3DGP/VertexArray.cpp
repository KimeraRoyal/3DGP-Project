#include "VertexArray.h"

#include <stdexcept>

VertexArray::VertexArray()
{
	// Generate vertex array object.
	m_vaoId = 0;
	glGenVertexArrays(1, &m_vaoId);
	if (!m_vaoId)
	{
		throw std::runtime_error("Failed to create vertex array.");
	}

	m_dirty = false;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vaoId);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_vaoId);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}