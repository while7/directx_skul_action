#pragma once
#include "singleton.h"

class Scene;

class SceneManager : public singleton<SceneManager>
{
private:

	Scene* m_nowScene;
	Scene* m_nextScene;
	map<string, Scene*> m_scenes;

	void Release();


public:
	SceneManager();
	virtual ~SceneManager();

	Scene* AddScene(const string& key, Scene* scenePtr);
	Scene* ChangeScene(const string& key);

	void Update();
	void Render();
};

#define SCENE SceneManager::GetInstance()