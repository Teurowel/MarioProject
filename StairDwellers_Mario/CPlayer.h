/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//Player class is the representation of player of our game
//It inherit from dynamic object class.
*//////////////////////////////////////////////////////////////////////

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CDynamicObject.h"
#include "CImgMgr.h"
#include "CInput.h"
#include "Enums.h"

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32

class CPlayer : public CDynamicObject
{
private :
	
	int m_iHealth;
	int m_iCoinScore = 0;

	bool m_bJump;
	bool m_bHasFired;
	bool m_bIsHit;
	bool m_bIsTransit;
	bool m_bIsInvincible;

	bulletType currentBullet;

	float m_fInvcCnt, m_fInvcMax;
	float m_fFlashCnt, m_fFlashMax;

public :
	CPlayer();
	CPlayer(const CPlayer& copy) {}
	CPlayer& operator=(const CPlayer& copy) {}
	virtual ~CPlayer() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

public :
	int getHealth() { return m_iHealth; }
	void SetCurrentBullet(bulletType eBulletType) { currentBullet = eBulletType; }
	bulletType getBulletType() { return currentBullet; }
	void AddCoinScore(int iScore) { m_iCoinScore += iScore; }
	int GetCoinScore() const { return m_iCoinScore; }
	void SetIsTransit(bool bTransit) {m_bIsTransit = bTransit;}
};

#endif