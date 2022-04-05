#include "Scene.h"

#include <iostream>


#include "Window.h"
#include "Shader.h"

#include "GameObject.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include "ModelComponent.h"

size_t Scene::s_lightPosKey = ShaderProgram::GetUniformKey("in_LightPos");

Scene::Scene()
{
	m_screen = std::make_unique<Screen>(m_programs.GetResource("data/shaders/screen"));
}

void Scene::Start()
{
	CreateGameObject()->AddComponent<CameraComponent>();
	m_light = CreateGameObject()->AddComponent<LightComponent>();

	std::shared_ptr<ModelComponent> model = CreateGameObject()->AddComponent<ModelComponent>();
	model->SetModel(m_models.GetResource("data/models/curuthers/curuthers.obj"));
	model->SetProgram(m_programs.GetResource("data/shaders/phong"));
	model->GetTransform()->SetPosition(glm::vec3(0.0f, -1.0f, -10.0f));

	std::shared_ptr<ModelComponent> model2 = CreateGameObject()->AddComponent<ModelComponent>();
	model2->SetModel(m_models.GetResource("data/models/curuthers/curuthers.obj"));
	model2->SetProgram(m_programs.GetResource("data/shaders/phong"));
	model2->GetTransform()->SetPosition(glm::vec3(3.0f, -1.0f, -8.0f));

	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->Start();
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