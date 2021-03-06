#pragma once

#include <memory>
#include <string>

#include "VertexBuffer.h"

class VertexArray
{
private:
	GLuint m_vaoId;

	std::vector<std::shared_ptr<VertexBuffer>> m_buffers;

	bool m_dirty;
public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray& _copy) = delete;
	VertexArray& operator=(const VertexArray& _other) = delete;

	void AddBuffer(const std::shared_ptr<VertexBuffer>& _buffer);

	[[nodiscard]] GLuint GetId();
	[[nodiscard]] unsigned int GetVertexCount();
};

