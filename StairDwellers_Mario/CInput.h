/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//Input class is the representation of event handler
//It will be used to check input of keyboard, mouse
//It will use SDL_Event
//Input class is singleton, so any class can access to get input
*//////////////////////////////////////////////////////////////////////

#ifndef _CINPUT_H_
#define _CINPUT_H_

#include "SingletonDefines.h"
#include <SDL.h>

class CInput
{
	DECLARE_SINGLETON(CInput)
private :
	const Uint8* m_iKeystates;

	int m_iMouseX;
	int m_iMouseY;

	bool m_bMouseLeft;

public :
	bool Init();
	bool HandleEvents();
	bool KeyDown(SDL_Scancode code);





	//Simple getter setter
public :
	int GetMouseX() const { return m_iMouseX; }
	int GetMouseY() const { return m_iMouseY; }
	bool GetMouseLeft() const { return m_bMouseLeft; }
};

#endif