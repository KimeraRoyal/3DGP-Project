#include "Scene.h"

#include <iostream>

#include "Window.h"
#include "Shader.h"

#include "GameObject.h"

size_t Scene::s_lightPosKey = std::hash<std::string>()("in_LightPos");

Scene::Scene(Resources* _resources)
	: m_renderingSystem(_resources)
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

	m_renderingSystem.PreDraw();
	
	glDisable(GL_DEPTH_TEST);
	
	/*												*
	 * PASS 2: LIGHTING PASS	*
	 *												*/
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