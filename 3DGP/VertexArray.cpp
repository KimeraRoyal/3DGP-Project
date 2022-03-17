#include "VertexArray.h"

#include <stdexcept>

VertexArray::VertexArray()
{
	// Generate vertex array object.
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

void VertexArray::Bind()
{
	glBindVertexArray(m_vaoId);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}