#include "CStaticObject.h"

#include "CTile.h"

CStaticObject::CStaticObject()
{

}

void CStaticObject::Update(double dDt)
{
	m_fPositionX += -CTile::s_fTileSpeed;
	m_desRect.x = (int)m_fPositionX;
}
