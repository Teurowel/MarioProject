#ifndef _CAUDIOMGR_H_
#define _CAUDIOMGR_H_

#include "SingletonDefines.h"
#include <map>
#include <SDL_mixer.h>
using namespace std;

class CAudioMgr
{
	DECLARE_SINGLETON(CAudioMgr)
private :
	map<const char*, Mix_Music*> m_mapMusic;
	map<const char*, Mix_Chunk*> m_mapSounds;

	int m_iVolume;

public :
	bool Init();
	void Shutdown();

	bool LoadMusic(const char* szPath, const char* szKey);
	bool LoadSound(const char* szPath, const char* szKey);
	void PlayMusic(const char* szKey, int loops = -1) const ;
	void StopMusic() const;
	void PlaySound(const char* szKey, int channel = -1, int loops = 0) const;
	void StopSound(int channel = -1) const;
	void SetMusicVolume(int v);
	void IncreaseMusicVolume();
	void DecreaseMusicVolume();
	void ToggleMusic();



private :
	void ShutdownMusic();
	void ShutdownSounds();
};

#endif
