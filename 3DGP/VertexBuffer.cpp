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
	m_dataType = 0;
}

VertexBuffer::~VertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_vboId);
}

void VertexBuffer::Add(const float _value)
{
	CompareDataType(GL_FLOAT);
	m_data.push_back(_value);
	m_dirty = true;
}

void VertexBuffer::Add(const glm::vec2 _value)
{
	CompareDataType(GL_FLOAT_VEC2);
	for(int i = 0; i < 2; i++)
	{
		m_data.push_back(_value[i]);
	}
	m_dirty = true;
}

void VertexBuffer::Add(const glm::vec3 _value)
{
	CompareDataType(GL_FLOAT_VEC3);
	for (int i = 0; i < 3; i++)
	{
		m_data.push_back(_value[i]);
	}
	m_dirty = true;
}

void VertexBuffer::Add(const glm::vec4 _value)
{
	CompareDataType(GL_FLOAT_VEC4);
	for (int i = 0; i < 4; i++)
	{
		m_data.push_back(_value[i]);
	}
	m_dirty = true;
}

void VertexBuffer::CompareDataType(const int _dataType)
{
	// Check if the vertex buffer has a data type already.
	if(!m_dataType) { m_dataType = _dataType; }
	else if(m_dataType != _dataType) { throw std::runtime_error("Tried to add a value to a vertex buffer of different value type."); }
}

GLuint VertexBuffer::GetId()
{
	if (m_dirty)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_data.at(0)) * m_data.size(), &m_data.at(0), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_dirty = false;
	}

	return m_vboId;
}

unsigned int VertexBuffer::GetDataSize() const
{
	return m_data.size() / GetDataTypeSize();
}

unsigned int VertexBuffer::GetDataTypeSize() const
{
	switch (m_dataType)
	{
	case GL_FLOAT:
		return 1;
	case GL_FLOAT_VEC2:
		return 2;
	case GL_FLOAT_VEC3:
		return 3;
	case GL_FLOAT_VEC4:
		return 4;
	default:
		throw std::runtime_error("Vertex buffer is using an unsupported data type.");
	}
}
