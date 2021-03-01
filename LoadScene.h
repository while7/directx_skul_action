#pragma once
#include "Scene.h"

struct Load
{
public:
	Load(const string& _Key, const string& _Path, int Size = 0) : m_Key(_Key), m_Path(_Path), m_Size(Size) { }
	~Load() {}
public:
	string m_Key;
	string m_Path;
	int m_Size = 0;
};

class LoadScene :
	public Scene
{
public:
	LoadScene();
	virtual ~LoadScene();

	Timer* timer;
	char str[256];

	virtual void Init()			override;
	virtual void Update()		override;
	virtual void Render()		override;
	virtual void Release()		override;
	void ImageLoad(const string& _Key, const string& _Path, int size = 0);
	int ImageCount = 0;
	int maxImageCount = 0;
	list<Load> Imagelist;
	list<Load> Anilist;
};