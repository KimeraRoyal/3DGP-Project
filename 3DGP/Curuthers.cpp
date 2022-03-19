#include "Curuthers.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"

Curuthers::Curuthers()
{
	// Vertex shaders
	const GLchar* vertexShaderSrc =
		"attribute vec3 in_Position;            " 													\
		"attribute vec2 in_TexCoord;"																				\
		""																																	\
		"uniform mat4 in_Projection;"																				\
		"uniform mat4 in_Model;"																						\
		"                                       "													  \
		"varying vec2 out_TexCoord;"																				\
		"                                       "														\
		"void main()                            "														\
		"{                                      "														\
		"	gl_Position = in_Projection * in_Model * vec4(in_Position, 1.0);"	\
		"	out_TexCoord = in_TexCoord;"																			\
		"}                                      ";

	// Fragment shaders
	const GLchar* fragmentShaderSrc =
		"uniform sampler2D in_Texture;"										\
		""																								\
		"varying vec2 out_TexCoord;"											\
		""																								\
		"void main()                       "							\
		"{                                 "							\
		"	vec4 tex = texture2D(in_Texture, out_TexCoord);"\
		" gl_FragColor = tex; "														\
		"}                                 ";

	m_texture = std::make_unique<Texture>("live_cat_reaction.png");

	m_curuthers = { 0 };
	if (WfModelLoad("models/curuthers/curuthers.obj", &m_curuthers) != 0)
	{
		throw std::runtime_error("Failed to load model.");
	}

	// Create program
	m_program = std::make_unique<Program>();

	// Create vertex array object
	m_vao = std::make_unique<VertexArray>();

	// Create vertex buffer object for positions
	std::shared_ptr<VertexBuffer> vboPosition = std::make_unique<VertexBuffer>();
	vboPosition->Add(glm::vec3(-0.5f, 0.5f, 0.0f));
	vboPosition->Add(glm::vec3(-0.5f, -0.5f, 0.0f));
	vboPosition->Add(glm::vec3(0.5f, 0.5f, 0.0f));
	vboPosition->Add(glm::vec3(-0.5f, -0.5f, 0.0f));
	vboPosition->Add(glm::vec3(0.5f, -0.5f, 0.0f));
	vboPosition->Add(glm::vec3(0.5f, 0.5f, 0.0f));

	// Create vertex buffer object for texture coordinates
	std::shared_ptr<VertexBuffer> vboTexcoords = std::make_unique<VertexBuffer>();
	vboTexcoords->Add(glm::vec2(0.0f, 0.0f));
	vboTexcoords->Add(glm::vec2(0.0f, 1.0f));
	vboTexcoords->Add(glm::vec2(1.0f, 0.0f));
	vboTexcoords->Add(glm::vec2(0.0f, 1.0f));
	vboTexcoords->Add(glm::vec2(1.0f, 1.0f));
	vboTexcoords->Add(glm::vec2(1.0f, 0.0f));

	// Add VBOs to VAO
	m_vao->AddBuffer(m_program->GetId(), "in_Position", vboPosition);
	m_vao->AddBuffer(m_program->GetId(), "in_Texcoord", vboTexcoords);
	glBindAttribLocation(m_program->GetId(), 2, "in_Normal");

	// Create and compile shaders
	std::shared_ptr<Shader> vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, vertexShaderSrc);
	std::shared_ptr<Shader> fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	// Attach shaders to program
	vertexShader->Attach(m_program->GetId());
	fragmentShader->Attach(m_program->GetId());

	// Link program
	m_program->Link();

	// Set uniforms
	m_modelLoc = glGetUniformLocation(m_program->GetId(), "in_Model");
	m_projectionLoc = glGetUniformLocation(m_program->GetId(), "in_Projection");
}

Curuthers::~Curuthers()
{
	
}

void Curuthers::Draw(std::weak_ptr<Time> _time)
{
	glm::mat4 persProjection = glm::perspective(glm::radians(45.0f), static_cast<float>(Window::GetWindowSize().x) / static_cast<float>(Window::GetWindowSize().y), 0.1f, 100.0f);
	glm::mat4 persModel(1.0f);
	persModel = glm::translate(persModel, glm::vec3(0, -3.0f, -10.0f));
	persModel = glm::scale(persModel, glm::vec3(1.0f, 1.0f, 1.0f));
	persModel = glm::rotate(persModel, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	glm::mat4 orthoProjection = glm::ortho(0.0f, static_cast<float>(Window::GetScaledWindowSize().x), 0.0f, static_cast<float>(Window::GetScaledWindowSize().y), 0.0f, 1.0f);
	glm::mat4 orthoModel(1.0f);
	orthoModel = glm::translate(orthoModel, glm::vec3(Window::GetScaledWindowSize().x / 2, Window::GetScaledWindowSize().y / 2, 0));
	orthoModel = glm::scale(orthoModel, glm::vec3(m_texture->GetSize().x, m_texture->GetSize().y, 1));

	glUseProgram(m_program->GetId());

	// Render Curuthers
	glBindVertexArray(m_curuthers.vaoId);
	glBindTexture(GL_TEXTURE_2D, m_curuthers.textureId);

	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(persModel));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(persProjection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glDrawArrays(GL_TRIANGLES, 0, m_curuthers.vertexCount);

	glDisable(GL_CULL_FACE);

	// Render GUI
	glBindVertexArray(m_vao->GetId());
	glBindTexture(GL_TEXTURE_2D, m_texture->GetId());

	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(orthoModel));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(orthoProjection));

	glDrawArrays(GL_TRIANGLES, 0, m_vao->GetVertexCount());

	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}