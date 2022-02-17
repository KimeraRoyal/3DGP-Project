#include "Triangle.h"

#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Window.h"

Triangle::Triangle()
{
	const GLfloat positions[] =
	{
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	const GLfloat textureCoordinates[] =
	{
		0.0f, 0.0f,
		0.0, 1.0f,
		1.0f, 1.0f,
	};

	// Load in texture file
	int w = 0;
	int h = 0;

	unsigned char* data = stbi_load("image.png", &w, &h, nullptr, 4);
	if (!data)
	{
		throw std::runtime_error("Failed to load texture \"image.png\"");
	}

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

	// Texture
	GLuint textureCoordVboId = 0;

	glGenBuffers(1, &textureCoordVboId);
	if (!textureCoordVboId)
	{
		throw std::runtime_error("Failed to generate texture coordinate buffer.");
	}

	glBindBuffer(GL_ARRAY_BUFFER, textureCoordVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Texture
	m_textureId = 0;
	
	glGenTextures(1, &m_textureId);
	if (!m_textureId)
	{
		throw std::runtime_error("Failed to create texture.");
	}

	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Vertex Shader
	const GLchar* vertexShaderSrc =
		"attribute vec3 in_Position;"											\
		"attribute vec2 in_TexCoord;"											\
		""																		\
		"uniform mat4 in_Projection;"											\
		"uniform mat4 in_Model;"												\
		""																		\
		"varying vec2 out_TexCoord;"											\
		""																		\
		"void main()"															\
		"{"																		\
		"	gl_Position = in_Projection * in_Model * vec4(in_Position, 1.0);"	\
		"	out_TexCoord = in_TexCoord;"										\
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
		"varying sampler2D in_Texture;"							\
		""														\
		"varying vec2 out_TexCoord;"							\
		""														\
		"void main()"											\
		"{"														\
		"	vec4 tex = texture2D(in_Texture, out_TexCoord);"	\
		"	gl_FragColor = tex;"								\
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
	glBindAttribLocation(m_programId, 1, "in_TexCoord");

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

	m_modelLoc = glGetUniformLocation(m_programId, "in_Model");
	m_projectionLoc = glGetUniformLocation(m_programId, "in_Projection");

	m_angle = 0;
}

Triangle::~Triangle()
{
	glDeleteProgram(m_programId);
}

void Triangle::Draw(std::unique_ptr<Time>& _time)
{
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window::GetWindowSize().x / (float)Window::GetWindowSize().y, 0.1f, 100.0f);
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, -2.5f));
	model = glm::rotate(model, glm::radians(m_angle), glm::vec3(0, 1, 0));

	m_angle += 15 * _time->GetDeltaTime();

	glUseProgram(m_programId);
	glBindVertexArray(m_vaoId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}