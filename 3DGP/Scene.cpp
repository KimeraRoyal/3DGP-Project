#include "Scene.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"

#include "WavefrontModel.h"

Scene::Scene()
{
	m_texture = std::make_unique<Texture>("data/live_cat_reaction.png");

	m_curuthers = std::make_unique<WavefrontModel>("data/models/curuthers/curuthers.obj");

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
	std::shared_ptr<Shader> vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, "data/shaders/phong.vert");
	std::shared_ptr<Shader> fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "data/shaders/phong.frag");

	// Attach shaders to program
	vertexShader->Attach(m_program->GetId());
	fragmentShader->Attach(m_program->GetId());

	// Link program
	m_program->Link();

	// Set uniforms
	m_viewLoc = m_program->GetUniformLocation("in_View");
	m_modelLoc = m_program->GetUniformLocation("in_Model");
	m_projectionLoc = m_program->GetUniformLocation("in_Projection");

	m_viewPosLoc = m_program->GetUniformLocation("in_ViewPos");
	m_lightPosLoc = m_program->GetUniformLocation("in_LightPos");

	m_light.GetTransform()->SetPosition(glm::vec3(-10.0f, 5.0f, -8.0f));
	m_curuthersTransform.SetPosition(glm::vec3(0.0f, -1.0f, -10.0f));
}

Scene::~Scene()
{
	
}

void Scene::Update(const std::shared_ptr<Time>& _time)
{
	//m_curuthersTransform.Rotate(glm::vec3(0, 10, 0) * _time->GetDeltaTime());

	m_camera.GetTransform()->SetPosition(glm::vec3(6.0f, 0.0f, 0.0f) * cos(_time->GetTime() / 2.0f));
	m_camera.GetTransform()->SetRotation(glm::vec3(0.0, 30.0f, 0.0f) * cos(_time->GetTime() / 2.0f));
	
	m_light.GetTransform()->SetPosition(glm::vec3(10.0f, 0.0f, 0.0f) * sin(_time->GetTime()));
}

void Scene::Draw(const std::shared_ptr<Time>& _time)
{
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Window::GetWindowSize().x) / static_cast<float>(Window::GetWindowSize().y), 0.1f, 100.0f);
	
	glUseProgram(m_program->GetId());
	
	// Render Curuthers
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera.GetViewMatrix()));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_curuthersTransform.GetModelMatrix()));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform3fv(m_viewPosLoc, 1, glm::value_ptr(m_camera.GetTransform()->GetPosition()));
	glUniform3fv(m_lightPosLoc, 1, glm::value_ptr(m_light.GetTransform()->GetPosition()));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_FRAMEBUFFER_SRGB);

	m_curuthers->Draw();

	glDisable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}