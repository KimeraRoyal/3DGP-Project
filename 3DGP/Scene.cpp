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

void Scene::Update(Time& _time, Input& _input)
{
	InitializeGameObjects();
	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (!gameObject->GetActive()) { continue; }
		gameObject->Update(_time, _input);
	}
	DisposeGameObjects();

	m_physicsSystem.Update(_time, m_gameObjects);
}

void Scene::Draw()
{
	/*												*
	 * PASS 1: RENDERING PASS						*
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
	 * PASS 2: LIGHTING PASS						*
	 *												*/
	glViewport(0, 0, Window::GetInstance()->GetScaledResolution().x, Window::GetInstance()->GetScaledResolution().y);
	m_screen->Bind();
	m_renderingSystem.Draw();
	m_screen->Unbind();

	glClear(GL_COLOR_BUFFER_BIT);

	if (Window::GetInstance()->GetSettings()->GetEnableSrgb()) { glEnable(GL_FRAMEBUFFER_SRGB); }
	m_screen->Draw();
	glDisable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_CULL_FACE);
}

std::shared_ptr<GameObject> Scene::CreatePrefab()
{
	std::shared_ptr<GameObject> prefab = std::shared_ptr<GameObject>(new GameObject);

	prefab->SetScene(shared_from_this());

	m_prefabs.push_back(prefab);

	return prefab;
}

std::shared_ptr<GameObject> Scene::CreateGameObject()
{
	std::shared_ptr<GameObject> gameObject = std::shared_ptr<GameObject>(new GameObject);

	gameObject->SetScene(shared_from_this());
	gameObject->OnCreate();
	
	m_toSpawn.push_back(gameObject);
	
	return gameObject;
}

std::shared_ptr<GameObject> Scene::CloneGameObject(const std::shared_ptr<GameObject>& _original)
{
	std::shared_ptr<GameObject> clone = std::shared_ptr<GameObject>(new GameObject);
	clone->Clone(_original);

	clone->SetScene(shared_from_this());
	clone->OnCreate();

	m_toSpawn.push_back(clone);

	return clone;
}

std::shared_ptr<GameObject> Scene::FindPrefabByName(const std::string& _name)
{
	for (const std::shared_ptr<GameObject>& gameObject : m_prefabs)
	{
		if (gameObject->GetName() == _name) { return gameObject; }
	}
	return nullptr;
}

std::shared_ptr<GameObject> Scene::FindGameObjectByName(const std::string& _name)
{
	for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject->GetName() == _name) { return gameObject; }
	}
	return nullptr;
}

void Scene::InitializeGameObjects()
{
	if (m_toSpawn.empty()) { return; }

	for (const std::shared_ptr<GameObject>& gameObject : m_toSpawn)
	{
		m_gameObjects.push_back(gameObject);
	}

	for (const std::shared_ptr<GameObject>& gameObject : m_toSpawn)
	{
		gameObject->Start();
	}

	m_toSpawn.clear();
}

void Scene::DisposeGameObjects()
{
	if (m_toDestroy.empty()) { return; }
	
	for (const std::shared_ptr<GameObject>& gameObject : m_toDestroy)
	{
		gameObject->OnDestroy();
		m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), gameObject));
	}
	m_toDestroy.clear();
}
