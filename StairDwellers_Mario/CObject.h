/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//Object class is the highest class in all object inheritance
*//////////////////////////////////////////////////////////////////////

#ifndef _COBJECT_H_
#define _COBJECT_H_

#include <SDL.h>

class CObject
{
protected :
	SDL_Rect m_srcRect;	//Rect that represents the area of Texture
	SDL_Rect m_desRect;	//Rect that represents the area where Texture will be drawn at screen

	float m_fPositionX;
	float m_fPositionY;

	bool m_bDelete;		//if true, delete object

public :
	CObject();
	CObject(const CObject& copy) {}
	CObject& operator=(const CObject& copy) {}
	virtual ~CObject() {}

	virtual bool Init() = 0;
	virtual void Update(double dDt) = 0;
	virtual void Render(SDL_Renderer* pRenderer) = 0;
	virtual void Shutdown() = 0;


	//Simple getter setter
public :
	const SDL_Rect* GetDesRect() const { return &m_desRect; }
	float GetPositionX() const { return m_fPositionX; }
	float GetPositionY() const { return m_fPositionY; }
	bool GetDelete() const { return m_bDelete; }
	
	
	void SetDelete(bool bDelete) { m_bDelete = bDelete; }
	void SetDestX(int DstX) { m_desRect.x = DstX; }
	void SetDestY(int DstY) { m_desRect.y = DstY; }
	void SetSrcRect(int x, int y, int w, int h) { m_srcRect.x = x, m_srcRect.y = y, m_srcRect.w = w, m_srcRect.h = h; }
	void SetX(float DestX) { m_fPositionX = DestX; }
	void SetY(float DestY) { m_fPositionY = DestY; }
};

#endif