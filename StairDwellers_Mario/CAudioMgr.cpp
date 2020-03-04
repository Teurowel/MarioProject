#include "CAudioMgr.h"
#include <iostream>
using namespace std;

IMPLEMENT_SINGLETON(CAudioMgr)

CAudioMgr::CAudioMgr()
	:m_iVolume(0)
{

}

bool CAudioMgr::Init()
{
	if (Mix_OpenAudio(13000, AUDIO_S16SYS, 2, 1000) == -1) // Good for most games.
		return false;

	Mix_AllocateChannels(30);

	m_iVolume = MIX_MAX_VOLUME - 70;
	SetMusicVolume(m_iVolume);

	return true;
}

void CAudioMgr::Shutdown()
{
	ShutdownMusic();
	ShutdownSounds();
}

bool CAudioMgr::LoadMusic(const char* szPath, const char* szKey)
{
	Mix_Music* pMusic = Mix_LoadMUS(szPath);

	if (pMusic != nullptr)
	{
		pair<map<const char*, Mix_Music*>::iterator, bool> ret;
		ret = m_mapMusic.insert(make_pair(szKey, pMusic));

		//if the same key value already exited,
		if (ret.second == false)
		{
			cout << szPath << " already exists" << endl;
			Mix_FreeMusic(pMusic);
			return false;
		}
	}
	else
	{
		cout << szPath << " Music load fail" << endl;
		return false;
	}

	return true;
}

bool CAudioMgr::LoadSound(const char* szPath, const char* szKey)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(szPath);

	if (pChunk != nullptr)
	{
		pair<map<const char*, Mix_Chunk*>::iterator, bool> ret;
		ret = m_mapSounds.insert(make_pair(szKey, pChunk));

		//if the same key value already exited,
		if (ret.second == false)
		{
			cout << szPath << " already exists" << endl;
			Mix_FreeChunk(pChunk);
			return false;
		}
	}
	else
	{
		cout << szPath << " Sound load fail" << endl;
		return false;
	}

	return true;
}

void CAudioMgr::PlayMusic(const char* szKey, int loops) const
{
	map<const char*, Mix_Music*>::const_iterator iter;

	//Find element with key value
	iter = m_mapMusic.find(szKey);

	//If there was no element,
	if (iter == m_mapMusic.end())
		return;
	else
		Mix_PlayMusic(iter->second, loops);
}

void CAudioMgr::StopMusic() const
{
	Mix_HaltMusic();
}

void CAudioMgr::PlaySound(const char* szKey, int channel, int loops) const
{
	map<const char*, Mix_Chunk*>::const_iterator iter;

	//Find element with key value
	iter = m_mapSounds.find(szKey);

	//If there was no element,
	if (iter == m_mapSounds.end())
		return;
	else
		Mix_PlayChannel(channel, iter->second, loops);
}

void CAudioMgr::StopSound(int channel) const
{
	Mix_HaltChannel(channel);
}

void CAudioMgr::SetMusicVolume(int v)
{
	v = (v < 0 ? 0 : (v > MIX_MAX_VOLUME ? MIX_MAX_VOLUME : v)); // Clamps vol from 0 to 128. 
	Mix_VolumeMusic(v);
}

void CAudioMgr::IncreaseMusicVolume()
{
	m_iVolume += 10;
	if (m_iVolume > MIX_MAX_VOLUME)
		m_iVolume = MIX_MAX_VOLUME; // 128.

	Mix_VolumeMusic(m_iVolume);
}

void CAudioMgr::DecreaseMusicVolume()
{
	m_iVolume -= 10;
	if (m_iVolume < 0)
		m_iVolume = 0;

	Mix_VolumeMusic(m_iVolume);
}

void CAudioMgr::ToggleMusic()
{
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void CAudioMgr::ShutdownMusic()
{
	map<const char*, Mix_Music*>::iterator iterBegin = m_mapMusic.begin();
	map<const char*, Mix_Music*>::iterator iterEnd = m_mapMusic.end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		Mix_FreeMusic(iterBegin->second);
		iterBegin->second = nullptr;
	}
	m_mapMusic.clear();
}

void CAudioMgr::ShutdownSounds()
{
	map<const char*, Mix_Chunk*>::iterator iterBegin = m_mapSounds.begin();
	map<const char*, Mix_Chunk*>::iterator iterEnd = m_mapSounds.end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		Mix_FreeChunk(iterBegin->second);
		iterBegin->second = nullptr;
	}
	m_mapSounds.clear();
}
