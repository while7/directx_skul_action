#include "DXUT.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_manager = new CSoundManager;
	m_manager->Initialize(DXUTGetHWND(), 2);
}

SoundManager::~SoundManager()
{
	for (auto iter : m_sounds)
		SAFE_DELETE(iter.second);
	m_sounds.clear();

	SAFE_DELETE(m_manager);
}

void SoundManager::AddSound(string key, wstring path)
{
	auto find = m_sounds.find(key);
	if (find != m_sounds.end())
		return;
	CSound* sound;
	m_manager->Create(&sound, (LPWSTR)path.c_str());
	m_sounds[key] = sound;
}

void SoundManager::Play(string key, BOOL isLoop)
{
	auto find = m_sounds.find(key);
	if (find == m_sounds.end())
		return;
	find->second->Play(0, isLoop);
}

void SoundManager::Copy(string key)
{
	auto find = m_sounds.find(key);
	if (find == m_sounds.end())
		return;
	LPDIRECTSOUNDBUFFER buff;
	m_manager->GetDirectSound()->DuplicateSoundBuffer(find->second->GetBuffer(0), &buff);
	buff->SetCurrentPosition(0);
	buff->Play(0, 0, 0);
}

void SoundManager::Stop(string key)
{
	auto find = m_sounds.find(key);
	if (find == m_sounds.end())
		return;
	find->second->Stop();
}