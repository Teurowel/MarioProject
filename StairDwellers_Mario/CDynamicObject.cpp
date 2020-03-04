#include "CDynamicObject.h"
#include "CObjMgr.h"
#include <list>

CDynamicObject::CDynamicObject()
	:m_bIsFacingRight(false),
	m_fFrameCtr(0),
	m_fFrameSpeed(0.f),
	m_iMoveFrameMax(0),
	m_fSpeed(0.f),
	m_fVelocityX(0.f),
	m_fVelocityY(0.f)
{

}

void CDynamicObject::Update(double dDt)
{
	//Gravity
	m_fVelocityY += 500.f * dDt;
}

CObject* CDynamicObject::checkBulletCollision()
{
	//Get bullet list
	SDL_Rect col;
	const SDL_Rect* pBulletRect = nullptr;
	const list<CObject*>* pBulletList = CObjMgr::GetInst()->GetObjList(OBJ_BULLET);
	list<CObject*>::const_iterator iterBegin = pBulletList->begin();
	list<CObject*>::const_iterator iterEnd = pBulletList->end();

	//Check bullet and enemy rect
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pBulletRect = (*iterBegin)->GetDesRect();
		if (SDL_IntersectRect(&m_desRect, pBulletRect, &col))
		{
			return *iterBegin;
		}
	}
	return nullptr;
}