#include "VertexArray.h"

#include <stdexcept>

VertexArray::VertexArray()
{
	// Generate vertex array object.
	m_vaoId = 0;
	glGenVertexArrays(1, &m_vaoId);
	if (!m_vaoId) { throw std::runtime_error("Failed to create vertex array."); }

	m_dirty = false;
}

VertexArray::~VertexArray()
{
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vaoId);
}

void VertexArray::AddBuffer(const std::shared_ptr<VertexBuffer>& _buffer)
{
	m_buffers.push_back(_buffer);

	m_dirty = true;
}

GLuint VertexArray::GetId()
{
	if(m_dirty)
	{
		// Bind the VBO (using the variable vaoId to avoid recursion)
		glBindVertexArray(m_vaoId);

		// Loop through each VBO, assigning them to the VAO
		for(unsigned int i = 0; i < m_buffers.size(); i++)
		{
			const unsigned int dataTypeSize = m_buffers.at(i)->GetDataTypeSize();

			// Bind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, m_buffers.at(i)->GetId());

			// Assign the VBO to position i on the VAO
			glVertexAttribPointer(i, dataTypeSize, GL_FLOAT, GL_FALSE, dataTypeSize * sizeof(GLfloat), static_cast<void*>(nullptr));
			glEnableVertexAttribArray(i);

			// Unbind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		// Unbind the VAO
		glBindVertexArray(0);
		
		m_dirty = false;
	}

	return m_vaoId;
}

unsigned VertexArray::GetVertexCount()
{
	return m_buffers.at(0)->GetDataSize();
}
