#pragma once
//#include "CEnemy.h"
#include "CStaticObject.h"

class Cannon : public CStaticObject
{
public:
	Cannon();
	Cannon(int iXpos, int iYpos);

	bool Init();
	void Update(double dDt);
	void Render(SDL_Renderer* pRenderer);
	void Shutdown();

	const char* m_szImgKey;

	bool m_bIsFacingRight;

	float m_iFireRate;
	float m_iFireRateMax;
};