#ifndef _CTIMEFONT_H
#define _CTIMEFONT_H

#include "CFont.h"

class CTimeFont : public CFont
{
private :
	double m_dAccumulatedTime;

public:
	CTimeFont();
	CTimeFont(string szString, SDL_Color fontColor, int iX, int iY);
	CTimeFont(const CTimeFont & copy) {}
	CTimeFont& operator=(const CTimeFont & copy) {}
	virtual ~CTimeFont() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();
};

#endif