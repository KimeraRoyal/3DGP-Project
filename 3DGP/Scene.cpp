#include "Scene.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"

#include "WavefrontModel.h"
#include "Quad.h"

#include "GameObject.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include "ModelComponent.h"

Scene::Scene()
{
	m_curuthers = std::make_unique<WavefrontModel>("data/models/curuthers/curuthers.obj");

	// Create program
	m_program = std::make_unique<ShaderProgram>();

	// Create and compile shaders
	Shader vertexShader = Shader(GL_VERTEX_SHADER, "data/shaders/phong.vert");
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, "data/shaders/phong.frag");

	// Attach shaders to program
	vertexShader.Attach(m_program->GetId());
	fragmentShader.Attach(m_program->GetId());

	m_program->BindAttribute("in_Position");
	m_program->BindAttribute("in_Texcoord");
	m_program->BindAttribute("in_Normal");

	// Link program
	m_program->Link();

	// Set uniforms
	m_viewLoc = m_program->GetUniformLocation("in_View");
	m_modelLoc = m_program->GetUniformLocation("in_Model");
	m_projectionLoc = m_program->GetUniformLocation("in_Projection");

	m_viewPosLoc = m_program->GetUniformLocation("in_ViewPos");
	m_lightPosLoc = m_program->GetUniformLocation("in_LightPos");

	m_screen = std::make_unique<Screen>("data/shaders/screen.vert", "data/shaders/screen.frag");
}

Scene::~Scene()
{
	
}

void Scene::Start()
{
	m_camera = CreateGameObject()->AddComponent<CameraComponent>();
	m_light = CreateGameObject()->AddComponent<LightComponent>();
	m_curuthersModel = CreateGameObject()->AddComponent<ModelComponent>();

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		AccessGameObject(i)->Start();
	}
}

void Scene::Update(const std::shared_ptr<Time>& _time)
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		AccessGameObject(i)->Update(_time);
	}
}

void Scene::Draw()
{
	m_screen->Bind();
	std::static_pointer_cast<CameraComponent>(m_camera)->Clear();
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Window::GetWindowSize().x) / static_cast<float>(Window::GetWindowSize().y), 0.1f, 100.0f);
	
	glUseProgram(m_program->GetId());
	
	// Render Curuthers
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(std::static_pointer_cast<CameraComponent>(m_camera)->GetViewMatrix()));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_curuthersModel->GetGameObject()->GetTransform()->GetModelMatrix()));
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform3fv(m_viewPosLoc, 1, glm::value_ptr(m_camera->GetGameObject()->GetTransform()->GetPosition()));
	glUniform3fv(m_lightPosLoc, 1, glm::value_ptr(m_light->GetGameObject()->GetTransform()->GetPosition()));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_curuthers->Draw();

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		AccessGameObject(i)->Draw();
	}
	m_screen->Unbind();

	glDisable(GL_DEPTH_TEST);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_FRAMEBUFFER_SRGB);
	m_screen->Draw();
	glDisable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_CULL_FACE);

	glUseProgram(0);
}

std::shared_ptr<GameObject> Scene::CreateGameObject()
{
	std::shared_ptr<GameObject> gameObject = std::shared_ptr<GameObject>(new GameObject);

	gameObject->SetScene(shared_from_this());
	m_gameObjects.push_back(gameObject);
	
	return gameObject;
}

std::shared_ptr<GameObject> Scene::AccessGameObject(const unsigned int _index)
{
	std::shared_ptr<GameObject> gameObject = m_gameObjects[_index].lock();
	if (!gameObject) { throw std::runtime_error("Tried to access scene's game object which no longer exists."); }
	return gameObject;
}
