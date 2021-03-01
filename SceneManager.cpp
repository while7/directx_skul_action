#include "DXUT.h"
#include "SceneManager.h"
#include "Scene.h"


SceneManager::SceneManager()
	: m_nowScene(nullptr), m_nextScene(nullptr)
{
}


SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Release()
{
	if (m_nowScene) 
		m_nowScene->Release();

	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();
}
Scene * SceneManager::AddScene(const string & key, Scene * scenePtr)
{
	if (!scenePtr)
		return nullptr;

	if (m_scenes.find(key) != m_scenes.end())
		return nullptr;

	m_scenes.insert(make_pair(key, scenePtr));
	return scenePtr;
}

Scene * SceneManager::ChangeScene(const string & key)
{
	auto find = m_scenes.find(key);
	if (find == m_scenes.end())
		return nullptr;

	OBJECT->ClearAllObjects();
	m_nextScene = find->second;

	return m_nextScene;
}

void SceneManager::Update()
{
	if (m_nextScene)
	{
		if (m_nowScene) {
			m_nowScene->Release();

		}
		m_nextScene->Init();
		m_nowScene = m_nextScene;
		m_nextScene = nullptr;
	}
	if (m_nowScene)
		m_nowScene->Update();
}

void SceneManager::Render()
{
	if (m_nowScene)
		m_nowScene->Render();
}
