#include "Scene.h"

#include <iostream>

#include "Window.h"
#include "Resources.h"

#include "Shader.h"

#include "GameObject.h"

size_t Scene::s_lightPosKey = std::hash<std::string>()("in_LightPos");

Scene::Scene(Settings* _settings, Resources* _resources)
	: m_physicsSystem(_settings->GetPhysicsTimestep()), m_renderingSystem(_resources)
{
	m_resources = _resources;

	m_screen = std::make_unique<Screen>(m_resources->GetProgram("data/shaders/screen/screen.vert", "data/shaders/screen/screen.frag"));
}

void Scene::Start()
{
	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(Time& _time, Input& _input)
{
	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (!gameObject->GetActive()) { continue; }
		gameObject->Update(_time, _input);
	}

	m_physicsSystem.Update(_time, m_gameObjects);
}

void Scene::Draw()
{
	/*												*
	 * PASS 1: RENDERING PASS	*
	 *												*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	glViewport(0, 0, Window::GetInstance()->GetResolution().x, Window::GetInstance()->GetResolution().y);
	m_renderingSystem.PreDraw();

	glDisable(GL_MULTISAMPLE);
	glDisable(GL_DEPTH_TEST);
	
	/*												*
	 * PASS 2: LIGHTING PASS	*
	 *												*/
	glViewport(0, 0, Window::GetInstance()->GetScaledResolution().x, Window::GetInstance()->GetScaledResolution().y);
	m_screen->Bind();
	m_renderingSystem.Draw();
	m_screen->Unbind();

	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_FRAMEBUFFER_SRGB);
	m_screen->Draw();
	glDisable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_CULL_FACE);
}

std::shared_ptr<GameObject> Scene::CreateGameObject()
{
	std::shared_ptr<GameObject> gameObject = std::shared_ptr<GameObject>(new GameObject);

	gameObject->SetScene(shared_from_this());
	gameObject->OnCreate();
	
	m_gameObjects.push_back(gameObject);
	
	return gameObject;
}