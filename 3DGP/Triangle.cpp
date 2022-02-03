#include "Triangle.h"

#include <stdexcept>

Triangle::Triangle()
{
	const GLfloat positions[] =
	{
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	// VBO
	GLuint positionsVboId = 0;

	glGenBuffers(1, &positionsVboId);
	if (!positionsVboId)
	{
		throw std::runtime_error("Failed to generate vertex buffer.");
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// VAO
	m_vaoId = 0;

	glGenVertexArrays(1, &m_vaoId);
	if (!m_vaoId)
	{
		throw std::runtime_error("Failed to create vertex array.");
	}

	glBindVertexArray(m_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Vertex Shader
	const GLchar* vertexShaderSrc =
		"attribute vec3 in_Position;"				\
		""											\
		"void main()"								\
		"{"											\
		"	gl_Position = vec4(in_Position, 1.0);"	\
		"}";

	m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShaderId, 1, &vertexShaderSrc, nullptr);
	glCompileShader(m_vertexShaderId);

	GLint success;
	glGetShaderiv(m_vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Failed to compile vertex shader!");
	}

	const GLchar* fragmentShaderSrc =
		"void main()"							\
		"{"										\
		"	gl_FragColor = vec4(1, 1, 1, 1);"	\
		"}";

	m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShaderId, 1, &fragmentShaderSrc, nullptr);
	glCompileShader(m_fragmentShaderId);
	glGetShaderiv(m_fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Failed to compile fragment shader!");
	}

	m_programId = glCreateProgram();
	glAttachShader(m_programId, m_vertexShaderId);
	glAttachShader(m_programId, m_fragmentShaderId);

	glBindAttribLocation(m_programId, 0, "in_Position");

	glLinkProgram(m_programId);
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Failed to link GL program!");
	}

	glDetachShader(m_programId, m_vertexShaderId);
	glDeleteShader(m_vertexShaderId);

	glDetachShader(m_programId, m_fragmentShaderId);
	glDeleteShader(m_fragmentShaderId);
}

Triangle::~Triangle()
{
	glDeleteProgram(m_programId);
}


void Triangle::Draw()
{
	glUseProgram(m_programId);
	glBindVertexArray(m_vaoId);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);
}