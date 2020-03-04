/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.20, 2019

//Enemy class is the base class of all enemies
//It inherit from dynamic object class.
*//////////////////////////////////////////////////////////////////////

#ifndef _CENEMY_H_
#define _CENEMY_H

#include "CDynamicObject.h"

class CEnemy : public CDynamicObject
{
public:
	CEnemy();
	CEnemy(const CEnemy& copy) {}
	CEnemy& operator=(const CEnemy& copy) {}
	virtual ~CEnemy() {}

	virtual bool Init() = 0;
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer) = 0;
	virtual void Shutdown() = 0;
	virtual void destroyEnemy() = 0;

	SDL_Rect* leftEdge;
	SDL_Rect* rightEdge;
	bool m_bCollide;
	bool m_bSafe;
	
	int m_iHealth;

	bool m_bIsStunned = false;
	float m_fStunTick = 0.0f;

	bool m_bIsShrunk = false;
	float m_fShrinkTick = 0.0f;

	float m_fMaxTick = 2.5f;
};

#endif