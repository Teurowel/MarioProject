/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Feb.15, 2019

//TitleBackGround class is the representation of background image in title
//It inherit from static object class.
*//////////////////////////////////////////////////////////////////////

#ifndef _CTITLEBACKGROUND_H_
#define _CTITLEBACKGROUND_H_

#include "CStaticObject.h"

class CTitleBackGround : public CStaticObject
{
private :
	const char* m_szImgKey;

public:
	CTitleBackGround();
	CTitleBackGround(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect);
	CTitleBackGround(const CTitleBackGround& copy) {}
	CTitleBackGround& operator=(const CTitleBackGround& copy) {}
	virtual ~CTitleBackGround() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

};

#endif