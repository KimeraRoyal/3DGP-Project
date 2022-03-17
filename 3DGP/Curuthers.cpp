#include "Curuthers.h"

#include <stdexcept>
#include <iostream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

Curuthers::Curuthers()
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

	// Loading model
	m_curuthers = { 0 };
	if (WfModelLoad("models/curuthers/curuthers.obj", &m_curuthers) != 0)
	{
		throw std::runtime_error("Failed to load model.");
	}

	// Create and bind vertex array

	// Create and bind position vertex buffer

	// Assign position buffer's data
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// Unbind position VBO

	// Create and bind texture coordinate vertex buffer

	// Assign texture coordinate buffer's data
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	// Unbind texture coordinate VBO
	
	// Unbind vertex array

	m_renderTexture = std::make_unique<RenderTexture>(150, 150);

	// Vertex Shader
	const GLchar* vertexShaderSrc =
		"#version 120\n"														\
		"attribute vec3 in_Position;"											\
		"attribute vec3 in_Normal;"												\
		"attribute vec2 in_TexCoord;"											\
		""																		\
		"uniform mat4 in_Projection;"											\
		"uniform mat4 in_Model;"												\
		""																		\
		"varying vec2 out_TexCoord;"											\
		""																		\
		"varying vec3 out_Normal;"												\
		"varying vec3 out_FragPos;"												\
		""																		\
		"void main()"															\
		"{"																		\
		"	gl_Position = in_Projection * in_Model * vec4(in_Position, 1.0);"	\
		"	out_TexCoord = in_TexCoord;"										\
		""																		\
		"	out_Normal = mat3(in_Model) * in_Normal;"							\
		"	out_FragPos = vec3(in_Model * vec4(in_Position, 1.0));"				\
		"}";

	const GLchar* fragmentShaderSrc =
		"#version 120\n"													\
		"uniform sampler2D in_Texture;"										\
		""																	\
		"varying vec2 out_TexCoord;"										\
		""																	\
		"varying vec3 out_Normal;"											\
		"varying vec3 out_FragPos;"											\
		""																	\
		"void main()"														\
		"{"																	\
		"	vec3 lightPos = vec3(5, 10, 10);"								\
		"	vec3 ambientColor = vec3(0.1, 0, 0.3);"							\
		"	vec3 diffuseColor = vec3(1, 1, 1);"								\
		"	vec3 specularColor = vec3(1, 0, 0);"							\
		""																	\
		"	vec3 normal = normalize(out_Normal);"							\
		"	vec3 lightDir = normalize(lightPos - out_FragPos);"				\
		"	float diff = max(dot(normal, lightDir), 0.0);"					\
		"	vec3 diffuse = diffuseColor * diff;"							\
		""																	\
		"	vec3 viewPos = vec3(0, 0, 0);"									\
		"	vec3 viewDir = normalize(viewPos - out_FragPos);"				\
		"	vec3 reflectDir = reflect(-lightDir, normal);"					\
		"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"		\
		"	vec3 specular = spec * specularColor;"							\
		""																	\
		"	vec3 lighting = min(ambientColor + diffuse + specular, 1.0);"	\
		"	vec4 tex = texture2D(in_Texture, out_TexCoord);"				\
		"	gl_FragColor = vec4(lighting, 1) * tex;"						\
		"}";
	//TODO: Use camera position to calculate view pos in code

	// Create vertex shader and compile
	
	// Create fragment shader and compile

	m_programId = glCreateProgram();

	glBindAttribLocation(m_programId, 0, "in_Position");
	glBindAttribLocation(m_programId, 1, "in_TexCoord");
	glBindAttribLocation(m_programId, 2, "in_Normal");

	glLinkProgram(m_programId);

	GLint success;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Failed to link GL program!");
	}

	// Set uniforms
	m_modelLoc = glGetUniformLocation(m_programId, "in_Model");
	m_projectionLoc = glGetUniformLocation(m_programId, "in_Projection");

	m_angle = 0;
}

Curuthers::~Curuthers()
{
	glDeleteProgram(m_programId);
}

void Curuthers::Draw(std::unique_ptr<Time>& _time)
{
	float scale = sin(_time->GetTime() * 0.1f) * 0.02f + 0.20f;
	float angleScale = sin(_time->GetTime() * 0.1f) * 30.0f;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window::GetWindowSize().x / (float)Window::GetWindowSize().y, 0.1f, 100.0f);
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, -0.2f, -2.5f));
	model = glm::rotate(model, glm::radians(angleScale), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(m_angle), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(scale, scale, scale));

	m_angle += 11 * _time->GetDeltaTime();

	glUseProgram(m_programId);
	glBindVertexArray(m_curuthers.vaoId);
	glBindTexture(GL_TEXTURE_2D, m_curuthers.textureId);

	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_renderTexture->Bind();
	glDrawArrays(GL_TRIANGLES, 0, m_curuthers.vertexCount);
	m_renderTexture->Unbind();
	glDrawArrays(GL_TRIANGLES, 0, m_curuthers.vertexCount);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}