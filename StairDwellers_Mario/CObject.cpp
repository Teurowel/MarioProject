#include "CObject.h"

CObject::CObject()
	:m_fPositionX(0.f),
	m_fPositionY(0.f),
	m_bDelete(false)
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 0;
	m_srcRect.h = 0;

	m_desRect.x = 0;
	m_desRect.y = 0;
	m_desRect.w = 0;
	m_desRect.h = 0;

}