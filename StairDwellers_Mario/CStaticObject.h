/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//Static Object class is the representation of static object in our game
//It inherit from Object class.
*//////////////////////////////////////////////////////////////////////

#ifndef _CSTATIC_OBJECT_H_
#define _CSTATIC_OBJECT_H_

#include "CObject.h"

class CStaticObject : public CObject
{
private :

public :
	CStaticObject();
	CStaticObject(const CStaticObject& copy) {}
	CStaticObject& operator=(const CStaticObject& copy) {}
	virtual ~CStaticObject() {}

	virtual bool Init() = 0;
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer) = 0;
	virtual void Shutdown() = 0;
};

#endif