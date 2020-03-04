#include "CBulletItem.h"

#include "CObjMgr.h"
#include "CObject.h"
#include "CImgMgr.h"
#include "CPlayer.h"
#include "CAudioMgr.h"

CBulletItem::CBulletItem()
{

}

CBulletItem::CBulletItem(int iXpos, int iYpos)
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = PROJECTILE_WIDTH;
	m_srcRect.h = PROJECTILE_HEIGHT;

	m_desRect.x = iXpos;
	m_fPositionX = iXpos;
	m_desRect.y = iYpos;
	m_fPositionY = iYpos;
	m_desRect.w = m_srcRect.w;
	m_desRect.h = m_srcRect.h;
}

bool CBulletItem::Init()
{

	return true;
}

void CBulletItem::Update(double dDt)
{
	CItem::Update(dDt);

	CObject* pPlayer = CObjMgr::GetInst()->GetObj(OBJ_PLAYER);
	//const SDL_Rect* pPlayerRect = CObjMgr::GetInst()->GetObj(OBJ_PLAYER)->GetDesRect();

	if (SDL_HasIntersection(pPlayer->GetDesRect(), &m_desRect))
	{
		((CPlayer*)pPlayer)->SetCurrentBullet(m_eBulletType);
		CObjMgr::GetInst()->GetObj(OBJ_UI)->SetSrcRect(16 * m_eBulletType, 0, 16, 16);
		m_bDelete = true;
		CAudioMgr::GetInst()->PlaySound("GetBullet");
	}
}

void CBulletItem::Render(SDL_Renderer * pRenderer)
{
	SDL_RenderCopy(pRenderer,	 CImgMgr::GetInst()->GetImg("Bullets"), &m_srcRect, &m_desRect);
}

void CBulletItem::Shutdown()
{

}

void CBulletItem::SetBulletType(bulletType eBulletType)
{
	m_eBulletType = eBulletType;
	m_srcRect.x = PROJECTILE_WIDTH * eBulletType;
}