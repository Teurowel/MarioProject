#include "CCoinItem.h"

#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CAudioMgr.h"

CCoinItem::CCoinItem()
{
}

CCoinItem::CCoinItem(int iXpos, int iYpos)
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = COINWIDTH;
	m_srcRect.h = COINHEIGHT;

	m_desRect.x = iXpos;
	m_fPositionX = iXpos;
	m_desRect.y = iYpos;
	m_fPositionY = iYpos;
	m_desRect.w = 16;
	m_desRect.h = 16;
}

bool CCoinItem::Init()
{
	return true;
}

void CCoinItem::Update(double dDt)
{
	CStaticObject::Update(dDt);

	CObject* pPlayer = CObjMgr::GetInst()->GetObj(OBJ_PLAYER);
	//const SDL_Rect* pPlayerRect = CObjMgr::GetInst()->GetObj(OBJ_PLAYER)->GetDesRect();

	if (SDL_HasIntersection(pPlayer->GetDesRect(), &m_desRect))
	{
		((CPlayer*)pPlayer)->AddCoinScore(1);
		m_bDelete = true;
		CAudioMgr::GetInst()->PlaySound("GetCoin");
	}
}

void CCoinItem::Render(SDL_Renderer * pRenderer)
{
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg("Coin"), &m_srcRect, &m_desRect);
}

void CCoinItem::Shutdown()
{
}
