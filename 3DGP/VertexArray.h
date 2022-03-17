#pragma once

#include <GL/glew.h>

class VertexArray
{
private:
	GLuint m_vaoId;

	bool m_dirty;
public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray& _copy) = delete;
	VertexArray& operator=(const VertexArray& _other) = delete;

	void Bind() const;
	void Unbind() const;

	GLuint GetId() const { return m_vaoId; }
};

