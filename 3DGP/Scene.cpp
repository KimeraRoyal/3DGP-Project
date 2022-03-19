#include "Scene.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"

Scene::Scene()
{
	m_texture = std::make_unique<Texture>("live_cat_reaction.png");

	m_curuthers = { 0 };
	if (WfModelLoad("models/curuthers/curuthers.obj", &m_curuthers) != 0)
	{
		throw std::runtime_error("Failed to load model.");
	}

	// Create vertex array object
	/*m_vao = std::make_unique<VertexArray>();

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
	m_vao->AddBuffer(m_program->GetId(), "in_Texcoord", vboTexcoords);*/

	// Create program
	m_program = std::make_unique<Program>();

	m_program->BindAttribute("in_Position");
	m_program->BindAttribute("in_Texcoord");
	m_program->BindAttribute("in_Normal");

	// Create and compile shaders
	std::shared_ptr<Shader> vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/phong.vert");
	std::shared_ptr<Shader> fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/phong.frag");

	// Attach shaders to program
	vertexShader->Attach(m_program->GetId());
	fragmentShader->Attach(m_program->GetId());

	// Link program
	m_program->Link();

	// Set uniforms
	m_viewLoc = m_program->GetUniformLocation("in_View");
	m_modelLoc = m_program->GetUniformLocation("in_Model");
	m_projectionLoc = m_program->GetUniformLocation("in_Projection");

	// Create program
	m_program2 = std::make_unique<Program>();

	m_program2->BindAttribute("in_Position");
	m_program2->BindAttribute("in_Texcoord");
	m_program2->BindAttribute("in_Normal");

	// Create and compile shaders
	std::shared_ptr<Shader> vertexShader2 = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/simple.vert");
	std::shared_ptr<Shader> fragmentShader2 = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/simple.frag");

	// Attach shaders to program
	vertexShader2->Attach(m_program2->GetId());
	fragmentShader2->Attach(m_program2->GetId());

	// Link program
	m_program2->Link();

	// Set uniforms
	m_viewLoc2 = m_program2->GetUniformLocation("in_View");
	m_modelLoc2 = m_program2->GetUniformLocation("in_Model");
	m_projectionLoc2 = m_program2->GetUniformLocation("in_Projection");
}

Scene::~Scene()
{
	
}

void Scene::Draw(const std::shared_ptr<Time>& _time)
{
	glm::mat4 viewMatrix = m_camera.GetTransform()->GetModelMatrix();
	viewMatrix = glm::inverse(viewMatrix);
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Window::GetWindowSize().x) / static_cast<float>(Window::GetWindowSize().y), 0.1f, 100.0f);
	m_curuthersTransform.Rotate(glm::vec3(0, 10, 0) * _time->GetDeltaTime());

	m_curuthersTransform.SetPosition(glm::vec3(-2.0f, -1.0f, -10.0f));
	
	glUseProgram(m_program->GetId());

	// Render Curuthers
	glBindVertexArray(m_curuthers.vaoId);
	glBindTexture(GL_TEXTURE_2D, m_curuthers.textureId);

	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_curuthersTransform.GetModelMatrix()));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glDrawArrays(GL_TRIANGLES, 0, m_curuthers.vertexCount);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}