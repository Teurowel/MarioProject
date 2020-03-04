/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.10, 2019

//Game class will handle entire game update, render
*//////////////////////////////////////////////////////////////////////


#ifndef _CGAME_H_
#define _CGAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SingletonDefines.h"

#define TILE_SIZE 16

class CStateMgr;
class CGame
{
	DECLARE_SINGLETON(CGame)
public :
	static bool s_bDebug;
	int m_hp;

	static const int SCREEN_WIDTH = (TILE_SIZE *2) * 28;
	static const int SCREEN_HEIGHT = (TILE_SIZE * 2) * 16;

private :
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	CStateMgr* m_pStateMgr;

	TTF_Font* m_pFont;

private :
	bool m_bRunning;

public :
	bool Init();
	void Update(double dDt);
	void Render();
	void Shutdown();

	void HandleEvenets();
	



private :
	bool InitSDL();
	void ShutdownSDL();

	
	bool LoadImages();		//Load Images
	bool LoadSound();		//Load music, sound effect


	//Simple getter setter
public :
	bool GetRunning() const { return m_bRunning; }
	SDL_Renderer* GetRenderer() const { return m_pRenderer;}
	CStateMgr* GetStateMgr() const { return m_pStateMgr; }
	TTF_Font* GetFont() const { return m_pFont; }
};

#endif