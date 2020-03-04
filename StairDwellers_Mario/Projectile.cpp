#include "Projectile.h"
#include "CObjMgr.h"
#include "CImgMgr.h"
#include "CGame.h"
#include "CTile.h"

Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

bool Projectile::Init()
{
	thisBullet = bulletType::DEFAULT;

	m_srcRect.x = m_srcRect.y = 0;
	m_srcRect.w = PROJECTILE_WIDTH;
	m_srcRect.h = PROJECTILE_HEIGHT;

	m_desRect.w = PROJECTILE_WIDTH;
	m_desRect.h = PROJECTILE_HEIGHT;

	return true;
}

void Projectile::setOrientation(const SDL_Rect& source, bool isRight)
{
	m_bIsFacingRight = isRight;

	m_fPositionX = m_bIsFacingRight ? source.x + source.w : source.x - m_srcRect.w;
	m_desRect.x = (int)m_fPositionX;

	m_fPositionY = source.y + m_srcRect.h / 2;
	m_desRect.y = (int)m_fPositionY;

	if(m_bIsFacingRight)
		m_fVelocityX = 400.f;
	else
		m_fVelocityX = -400.f;
}

void Projectile::Update(double dDt)
{
	m_fPositionX += m_fVelocityX * dDt - CTile::s_fTileSpeed;
	m_desRect.x = (int)m_fPositionX;

	//m_desRect.x += m_bIsFacingRight ? m_fSpeed : -m_fSpeed;

	if (m_desRect.x > CGame::SCREEN_WIDTH + 20 || m_desRect.x < -20)
		m_bDelete = true;
	if (m_desRect.y > CGame::SCREEN_HEIGHT + 20 || m_desRect.y < -20)
		m_bDelete = true;

	SDL_Rect col;
	list<CObject*>::const_iterator iterBegin;
	list<CObject*>::const_iterator iterEnd;

	Projectile* bullet = dynamic_cast<Projectile*>(checkBulletCollision());
	if (bullet != nullptr && bullet != this)
	{
		switch (getBulletType())
		{
		case bulletType::METAL:
			bullet->SetDelete(true);
				break;
		case bulletType::DEFAULT:
			if(bullet->getBulletType() == bulletType::DEFAULT ||
				bullet->getBulletType() == bulletType::METAL)
				SetDelete(true);
			if(bullet->getBulletType() != bulletType::METAL)
				bullet->SetDelete(true);
			break;
		case bulletType::FIRE:
		case bulletType::SHRINK:
			SetDelete(true);
			break;
		}
	}

	//Collision check with tile
	SDL_Rect tempRect = m_desRect;
	float fTempPositionX = m_fPositionX;

	fTempPositionX += m_fVelocityX * dDt;
	tempRect.x = (int)fTempPositionX;

	const SDL_Rect* pTileRect;
	//Get tile list
	const list<CObject*>* pTileList = CObjMgr::GetInst()->GetObjList(OBJ_GROUNDTILE);

	iterBegin = pTileList->begin();
	iterEnd = pTileList->end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pTileRect = (*iterBegin)->GetDesRect();
		if ((pTileRect->x + pTileRect->w) > 0 && pTileRect->x < CGame::SCREEN_WIDTH)
		{
			if (SDL_IntersectRect(&tempRect, pTileRect, &col))
			{
				m_bDelete = true;
			}
		}
	}
}

void Projectile::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Bullets"), &m_srcRect, &m_desRect, 0, nullptr, m_bIsFacingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Projectile::Shutdown()
{
	
}