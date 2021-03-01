#pragma once
#include "singleton.h"

class SoundManager : public singleton<SoundManager>
{
private:
	map<string, CSound*> m_sounds;
	CSoundManager* m_manager;
public:
	SoundManager();
	virtual ~SoundManager();

	void AddSound(string str, wstring path);
	void Play(string str, BOOL isLoop);
	void Copy(string str);
	void Stop(string str);
};

#define SOUND SoundManager::GetInstance()