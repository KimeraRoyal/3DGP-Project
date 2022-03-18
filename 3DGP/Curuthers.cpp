#include "Curuthers.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

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
	
	const GLchar* vertexShaderSrc2 =
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
	
	const GLchar* fragmentShaderSrc2 =
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

	m_texture = std::make_unique<Texture>("image.png");

	// Create program
	m_program = std::make_unique<Program>();

	// Create vertex array object
	m_vao = std::make_unique<VertexArray>();

	// Create vertex buffer object for positions
	std::shared_ptr<VertexBuffer> vboPosition = std::make_unique<VertexBuffer>();
	vboPosition->Add(glm::vec3(0.0f, 0.5f, 0.0f));
	vboPosition->Add(glm::vec3(-0.5f, -0.5f, 0.0f));
	vboPosition->Add(glm::vec3(0.5f, -0.5f, 0.0f));

	// Create vertex buffer object for texture coordinates
	std::shared_ptr<VertexBuffer> vboTexcoords = std::make_unique<VertexBuffer>();
	vboTexcoords->Add(glm::vec2(0.0f, 0.0f));
	vboTexcoords->Add(glm::vec2(0.0f, 1.0f));
	vboTexcoords->Add(glm::vec2(1.0f, 1.0f));

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

	m_angle = 0;
}

Curuthers::~Curuthers()
{
	
}

void Curuthers::Draw(std::unique_ptr<Time>& _time)
{
	float scale = sin(_time->GetTime() * 0.1f) * 0.2f + 0.20f;
	float angleScale = sin(_time->GetTime() * 0.1f) * 30.0f;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Window::GetWindowSize().x) / static_cast<float>(Window::GetWindowSize().y), 0.1f, 100.0f);
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, -0.2f, -2.5f));
	model = glm::rotate(model, glm::radians(angleScale), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(m_angle), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(scale, scale, scale));

	m_angle += 11 * _time->GetDeltaTime();

	glUseProgram(m_program->GetId());
	glBindVertexArray(m_vao->GetId());
	glBindTexture(GL_TEXTURE_2D, m_texture->GetId());

	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glDrawArrays(GL_TRIANGLES, 0, m_vao->GetVertexCount());

	glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}