/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang, Russell
Last Updated : Jan.11, 2019

//ImgMgr class is the singleton class that will handle all image in game
*//////////////////////////////////////////////////////////////////////

#ifndef _CIMGMGR_H_
#define _CIMGMGR_H_

#include "SingletonDefines.h"
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class CImgMgr
{
	DECLARE_SINGLETON(CImgMgr)
private :
	map<const char*, SDL_Texture*> m_mapImg;

public :
	bool Init();
	void Shutdown();

public :
	bool AddImg(const char* szImagePath, const char* szImageKey, SDL_Renderer* pRenderer);
	SDL_Texture* GetImg(const char* szImageKey) const;
};

#endif