#ifndef _CCOINSCOREFONT_H
#define _CCOINSCOREFONT_H

#include "CFont.h"

class CCoinScoreFont : public CFont
{
private :
	SDL_Rect m_coinSrcRect;	//coin image
	SDL_Rect m_coindDesRect;

public:
	CCoinScoreFont();
	CCoinScoreFont(string szString, SDL_Color fontColor, int iX, int iY);
	CCoinScoreFont(const CCoinScoreFont& copy) {}
	CCoinScoreFont& operator=(const CCoinScoreFont& copy) {}
	virtual ~CCoinScoreFont() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();
};

#endif