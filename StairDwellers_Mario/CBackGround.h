/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//BackGround class is the representation of background image in our game
//It inherit from static object class.
*//////////////////////////////////////////////////////////////////////

#ifndef _CBACKGROUND_H_
#define _CBACKGROUND_H_

#include "CStaticObject.h"
#include "CImgMgr.h"

class CBackGround : public CStaticObject
{
private :
	float m_fSecondPositionX;
	SDL_Rect m_SecondDesRect;		//We draw background twice for moving
	const char* m_szImgKey;

public :
	CBackGround();
	CBackGround(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect);
	CBackGround(const CBackGround & copy) {}
	CBackGround& operator=(const CBackGround & copy) {}
	virtual ~CBackGround() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();
};

#endif