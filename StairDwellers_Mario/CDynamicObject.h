/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//Dynamic Object class is the representation of dynamic object in our game
//It inherit from Object class.
*//////////////////////////////////////////////////////////////////////

#ifndef _CDYNAMIC_OBJECT_H_
#define _CDYNAMIC_OBJECT_H_

#include "CObject.h"

class CDynamicObject : public CObject
{
protected :
	bool m_bIsFacingRight;	//false if character is facing left

	float m_fFrameCtr;		//sprite frame counter
	float m_fFrameSpeed;	//sprite frame change speed
	int m_iMoveFrameMax;

	float m_fSpeed;		//Speed is just value
	float m_fVelocityX; //velocity will be speed with direction
	float m_fVelocityY;
		
public :
	CDynamicObject();
	CDynamicObject(const CDynamicObject& copy) {}
	CDynamicObject& operator=(const CDynamicObject& copy) {}
	virtual ~CDynamicObject() {}

	virtual bool Init() = 0;
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer) = 0;
	virtual void Shutdown() = 0;

	CObject* checkBulletCollision();


	//Simple getter setter
public :
	bool GetIsFacingRight() const { return m_bIsFacingRight; }
	float GetSpeed() const { return m_fSpeed; }
	float GetVelocityX() const { return m_fVelocityX; }
	void SetIsFacingRight(bool Flip) { m_bIsFacingRight = Flip; }
};

#endif