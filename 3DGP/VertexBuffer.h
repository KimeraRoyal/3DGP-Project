#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class VertexBuffer
{
private:
	GLuint m_vboId;

	std::vector<float> m_data;
	int m_dataType;

	bool m_dirty;

	void CompareDataType(int _dataType);
public:
	VertexBuffer();
	~VertexBuffer();

	VertexBuffer(const VertexBuffer& _copy) = delete;
	VertexBuffer& operator=(const VertexBuffer& _other) = delete;

	void Add(float _value);
	void Add(glm::vec2 _value);
	void Add(glm::vec3 _value);
	void Add(glm::vec4 _value);

	[[nodiscard]] GLuint GetId();
	[[nodiscard]] unsigned int GetDataSize() const;
	[[nodiscard]] unsigned int GetDataTypeSize() const;
};

