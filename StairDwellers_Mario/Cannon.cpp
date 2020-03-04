#include "Cannon.h"
#include "CGame.h"
#include "CObjMgr.h"
#include "CImgMgr.h"
#include "CAudioMgr.h"
#include "Projectile.h"

Cannon::Cannon()
{
}

Cannon::Cannon(int iXpos, int iYpos)
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 16;
	m_srcRect.h = 16;

	m_desRect.x = iXpos;
	m_fPositionX = iXpos;
	m_desRect.y = iYpos;
	m_fPositionY = iYpos;
	m_desRect.w = m_srcRect.w * 2;
	m_desRect.h = m_srcRect.h * 2;
}

bool Cannon::Init()
{
	m_iFireRate = 0;
	m_iFireRateMax = 2;

	return true;
}

void Cannon::Update(double dDt)
{
	CStaticObject::Update(dDt);

	SDL_Rect center = m_desRect;
	center.x += center.w / 2;
	center.y += center.h / 2;

	CObject* player = CObjMgr::GetInst()->GetObj(OBJ_PLAYER, 0);

	if (center.x > 0 && center.x < CGame::SCREEN_WIDTH)
	{
		m_bIsFacingRight = player->GetDesRect()->x < center.x ? false : true;

		if (m_iFireRate >= m_iFireRateMax)
		{
			Projectile* pProjectile = new Projectile();

			pProjectile->Init();
			pProjectile->setOrientation(m_desRect, m_bIsFacingRight);
			CObjMgr::GetInst()->AddObj(pProjectile, OBJ_BULLET);
			CAudioMgr::GetInst()->PlaySound("Bullet");

			m_iFireRate = 0;
		}
		else
		{
			m_iFireRate += dDt;
		}
	}
}

void Cannon::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg("Cannon"), &m_srcRect, &m_desRect);
}

void Cannon::Shutdown()
{

}