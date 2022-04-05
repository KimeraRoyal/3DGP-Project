#include "Scene.h"

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
	CreateGameObject()->AddComponent<CameraComponent>();
	m_light = CreateGameObject()->AddComponent<LightComponent>();

	const std::shared_ptr<IModel> curuthersModel = std::make_unique<WavefrontModel>("data/models/curuthers/curuthers.obj");

	std::shared_ptr<ModelComponent> model = CreateGameObject()->AddComponent<ModelComponent>();
	model->SetModel(curuthersModel);
	model->SetProgram(m_program);
	model->GetTransform()->SetPosition(glm::vec3(0.0f, -1.0f, -10.0f));

	std::shared_ptr<ModelComponent> model2 = CreateGameObject()->AddComponent<ModelComponent>();
	model2->SetModel(curuthersModel);
	model2->SetProgram(m_program);
	model2->GetTransform()->SetPosition(glm::vec3(3.0f, -1.0f, -8.0f));

	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->Start();
	}

	std::vector<std::shared_ptr<ModelComponent>> modelComponents;
	FindComponents<ModelComponent>(modelComponents);
	for(std::shared_ptr<ModelComponent> modelComponent : modelComponents)
	{
		std::printf("Model found!\n");
	}
}

void Scene::Update(const std::shared_ptr<Time>& _time)
{
	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->Update(_time);
	}
}

void Scene::Draw()
{
	m_screen->Bind();
	// Light position
	glUniform3fv(m_lightPosLoc, 1, glm::value_ptr(m_light->GetGameObject()->GetTransform()->GetPosition()));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->PreDraw();
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