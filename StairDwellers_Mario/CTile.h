#ifndef _CTILE_H_
#define _CTILE_H_

#include "CStaticObject.h"

class CTile : public CStaticObject
{
public :
	static float s_fTileLeftOffset;	//where tile start to move to right
	static float s_fTileSpeed;	//TIle moving speed

	const char* m_szImgKey;
public :
	CTile();
	CTile(int iXpos, int iYpos);
	CTile(const char* szImgKey, int iXpos, int iYpos, int iSrcX, int iSrcY);
	CTile(const char* szImgKey, int iXpos, int iYpos, int iSrcX, int iSrcY, const SDL_Rect& boundRect);
	CTile(int iXpos, int iYpos, int iSrcX, int iSrcY);
	CTile(const CTile& copy) {}
	CTile& operator=(const CTile& copy) {}
	virtual ~CTile() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();



	//simpel getter setter
public :
	float GetTileSpeed() const { return s_fTileSpeed; }
};

#endif