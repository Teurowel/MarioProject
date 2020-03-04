#ifndef _CFONT_H
#define _CFONT_H

#include "CStaticObject.h"
#include <string>
using namespace std;

class CFont : public CStaticObject
{
protected :
	string m_szString;
	string m_szPrevString;
	SDL_Color m_FontColor;
	
	SDL_Surface* m_pFontSurface;
	SDL_Texture* m_pFontTexture;

	SDL_Rect m_rFontRect;

	double m_dMaxExistTime;
	double m_dExistTime;
public:
	CFont();
	CFont(string szString, SDL_Color fontColor, int iX, int iY, double dMaxExistTime = 0);
	CFont(const CFont & copy) {}
	CFont& operator=(const CFont & copy) {}
	virtual ~CFont() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();
};

#endif