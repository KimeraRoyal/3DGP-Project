#include "Scene.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"

#include "WavefrontModel.h"

#include "GameObject.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include "ModelComponent.h"

Scene::Scene()
{
	// Create program
	m_program = std::make_unique<ShaderProgram>("data/shaders/phong.vert", "data/shaders/phong.frag");

	// Set uniforms
	m_viewLoc = m_program->GetUniformLocation("in_View");
	m_modelMatrixLoc = m_program->GetUniformLocation("in_Model");
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

	std::shared_ptr<ModelComponent> curuthersModel = std::make_unique<ModelComponent>();
	curuthersModel->SetModel(std::make_unique<WavefrontModel>("data/models/curuthers/curuthers.obj"));
	curuthersModel->SetProgram(m_program);
	m_model = CreateGameObject()->AddComponent(curuthersModel);

	for (auto& m_gameObject : m_gameObjects)
	{
		m_gameObject.Start();
	}

	for (auto& m_gameObject : m_gameObjects)
	{
		glm::vec3 val = m_gameObject.GetTransform()->GetPosition();
		std::printf("pX: %f pY: %f pZ: %f ", val.x, val.y, val.z);
		val = m_gameObject.GetTransform()->GetScale();
		std::printf("sX: %f sY: %f sZ: %f ", val.x, val.y, val.z);
		val = m_gameObject.GetTransform()->GetRotation();
		std::printf("rX: %f rY: %f rZ: %f\n", val.x, val.y, val.z);
	}
}

void Scene::Update(const std::shared_ptr<Time>& _time)
{
	for(auto & m_gameObject : m_gameObjects)
	{
		m_gameObject.Update(_time);
	}
}

void Scene::Draw()
{
	m_screen->Bind();
	std::static_pointer_cast<CameraComponent>(m_camera)->Clear();

	const glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Window::GetWindowSize().x) / static_cast<float>(Window::GetWindowSize().y), 0.1f, 100.0f);
	
	m_program->Bind();
	
	// Render Curuthers
	m_program->SetUniformValue(m_viewLoc, std::static_pointer_cast<CameraComponent>(m_camera)->GetViewMatrix());
	m_program->SetUniformValue(m_modelMatrixLoc, m_model->GetGameObject()->GetTransform()->GetModelMatrix());
	m_program->SetUniformValue(m_projectionLoc, projection);
	
	m_program->SetUniformValue(m_viewPosLoc, m_camera->GetGameObject()->GetTransform()->GetPosition());
	m_program->SetUniformValue(m_lightPosLoc, m_light->GetGameObject()->GetTransform()->GetPosition());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	for (auto& m_gameObject : m_gameObjects)
	{
		m_gameObject.Draw();
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

GameObject* Scene::CreateGameObject()
{
	GameObject gameObject;
	if(!m_inactiveGameObjects.empty())
	{
		gameObject = std::move(m_inactiveGameObjects.top());
		m_inactiveGameObjects.pop();
	}
	
	gameObject.SetScene(shared_from_this());
	m_gameObjects.push_back(std::move(gameObject));
	
	return &m_gameObjects.back();
}

void Scene::DestroyGameObject(GameObject* _gameObject)
{
	_gameObject->Disable();
	_gameObject->SetScene(nullptr);
	
	const std::vector<GameObject>::iterator iterator = std::find(m_gameObjects.begin(), m_gameObjects.end(), *_gameObject);
	m_inactiveGameObjects.push(std::move(*_gameObject));
	m_gameObjects.erase(iterator);
}