#include "FireBullet.h"
#include "CImgMgr.h"
#include "CGame.h"
#include "CObjMgr.h"
#include "CTile.h"

#include <iostream>

FireBullet::FireBullet()
{
}

FireBullet::~FireBullet()
{
}

bool FireBullet::Init()
{
	thisBullet = bulletType::FIRE;

	m_srcRect.x = 16;
	m_srcRect.y = 0;
	m_srcRect.w = PROJECTILE_WIDTH;
	m_srcRect.h = PROJECTILE_HEIGHT;

	m_desRect.w = PROJECTILE_WIDTH;
	m_desRect.h = PROJECTILE_HEIGHT;

	m_fAnimCnt = 0;
	m_fAnimMax = 0.2f;

	return true;
}

void FireBullet::spawnNewBullet(int angle, int velocityX)
{
	FireBullet* pProjectile = new FireBullet();

	pProjectile->m_fAngle = angle;
	pProjectile->Init();
	pProjectile->m_fPositionX = m_desRect.x;
	pProjectile->m_fPositionY = m_desRect.y;
	pProjectile->m_desRect = m_desRect;

	if (m_bIsFacingRight)
	{
		if (angle > 0)
		{
			pProjectile->m_fPositionY += pProjectile->m_desRect.h + 2;
			pProjectile->m_desRect.y += pProjectile->m_desRect.h + 2;
		}
		else
		{
			pProjectile->m_fPositionY -= pProjectile->m_desRect.h + 2;
			pProjectile->m_desRect.y -= pProjectile->m_desRect.h + 2;;
		}
	}
	else
	{
		if (angle < 0)
		{
			pProjectile->m_fPositionY += pProjectile->m_desRect.h + 2;
			pProjectile->m_desRect.y += pProjectile->m_desRect.h + 2;
		}
		else
		{
			pProjectile->m_fPositionY -= pProjectile->m_desRect.h + 2;
			pProjectile->m_desRect.y -= pProjectile->m_desRect.h + 2;;
		}
	}

	//pProjectile->m_desRect.x += 50;

	pProjectile->m_bIsFacingRight = m_bIsFacingRight;
	CObjMgr::GetInst()->AddObj(pProjectile, OBJ_BULLET);

	pProjectile->m_fVelocityX = velocityX;
	//m_fVelocityY = angle > 0 ? (m_fVelocityX > 0 ? m_fVelocityX / 2 : -m_fVelocityX / 2) : (m_fVelocityX > 0 ? -m_fVelocityX / 2 : m_fVelocityX / 2);
	if (angle > 0)
		pProjectile->m_fVelocityY = velocityX * 0.5f;
	else
		pProjectile->m_fVelocityY = -velocityX * 0.5f;
}

void FireBullet::setOrientation(const SDL_Rect& source, bool isRight)
{
	Projectile::setOrientation(source, isRight);

	if (m_fAngle != 45 && m_fAngle != -45)
	{
		FireBullet::spawnNewBullet(45, m_fVelocityX);
		FireBullet::spawnNewBullet(-45, m_fVelocityX);
	}
}

void FireBullet::Update(double deltatime)
{
	Projectile::Update(deltatime);

	if (m_fAngle != 0)
	{
		m_fPositionY += m_fVelocityY * deltatime;
		m_desRect.y = (int)m_fPositionY;
	}

	m_fAnimCnt += deltatime;
	if (m_fAnimCnt >= m_fAnimMax * 2)
		m_fAnimCnt = 0;
	if (m_fAnimCnt < m_fAnimMax)
		m_srcRect.y = 0;
	else
		m_srcRect.y = 16;

}

void FireBullet::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Bullets"), &m_srcRect, &m_desRect, m_fAngle, nullptr, m_bIsFacingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

