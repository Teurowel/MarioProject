/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.20, 2019

//Turtle class is one of the enemies of our game
//It inherit from enemy class.
*//////////////////////////////////////////////////////////////////////

#ifndef _CTURTLE_H_
#define _CTURTLE_H_

#include "CEnemy.h"

class CTurtle : public CEnemy
{
private :


public:
	CTurtle();
	CTurtle(int iXpos, int iYpos);
	CTurtle(const CTurtle& copy) {}
	CTurtle& operator=(const CTurtle& copy) {}
	virtual ~CTurtle() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

	void destroyEnemy();
};

#endif