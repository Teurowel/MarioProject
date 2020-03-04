#include "CTurtle.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "GoldProjectile.h"
#include "CDynamicObject.h"
#include "Projectile.h"
#include "CTile.h"
#include "CGame.h"
#include "CAudioMgr.h"

CTurtle::CTurtle()
{

}

CTurtle::CTurtle(int iXpos, int iYpos)
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 16;
	m_srcRect.h = 28;

	m_desRect.x = iXpos;
	m_fPositionX = iXpos;
	m_desRect.y = iYpos;
	m_fPositionY = iYpos;
	m_desRect.w = m_srcRect.w * 2;
	m_desRect.h = m_srcRect.h * 2;
}

bool CTurtle::Init()
{
	m_fSpeed = 50.f;
	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;

	m_bIsFacingRight = false;
	m_bCollide = false;
	m_bSafe = false;

	m_fFrameSpeed = 10.f;
	m_iMoveFrameMax = 2;

	leftEdge = new SDL_Rect();
	leftEdge->w = 32;
	leftEdge->h = 8;
	leftEdge->x = m_desRect.x - leftEdge->w;
	leftEdge->y = m_desRect.y + m_desRect.h;

	rightEdge = new SDL_Rect();
	rightEdge->w = 32;
	rightEdge->h = 8;
	rightEdge->x = m_desRect.x + m_desRect.w;
	rightEdge->y = m_desRect.y + m_desRect.h;

	return true;
}

void CTurtle::Update(double dDt)
{

	SDL_Rect col;
	list<CObject*>::const_iterator iterBegin;
	list<CObject*>::const_iterator iterEnd;

	Projectile* bullet = dynamic_cast<Projectile*>(checkBulletCollision());
	if (bullet != nullptr)
	{
		if (bullet->getBulletType() == bulletType::SHRINK)
		{
			if (!m_bIsShrunk)
			{
				m_bIsShrunk = true;
				CAudioMgr::GetInst()->PlaySound("Koopa");
				m_desRect.w /= 2;
				m_desRect.h /= 2;
			}
		}
		else if (bullet->getBulletType() == bulletType::METAL)
		{
			GoldProjectile* pProjectile;
			pProjectile = new GoldProjectile;
			// Projectile* pProjectile = new Projectile;
			pProjectile->Init();
			pProjectile->setOrientation(m_desRect, m_bIsFacingRight);
			CObjMgr::GetInst()->AddObj(pProjectile, OBJ_BULLET);
			bullet->SetDelete(true);
			//(*iterBegin)->SetDelete(true);
			// CAudioMgr::GetInst()->PlaySound("Bullet");
		}
		else
		{
			CAudioMgr::GetInst()->PlaySound("Koopa");
			destroyEnemy();
			bullet->SetDelete(true);
			return;
		}
	}

	CDynamicObject::Update(dDt);

	//Give X velocity
	if (m_bIsFacingRight == false)
		m_fVelocityX = -m_fSpeed;
	else
		m_fVelocityX = m_fSpeed;


	//Horizontal Col check
	if (m_fVelocityX != 0)
	{
		SDL_Rect tempRect = m_desRect;
		float fTempPositionX = m_fPositionX;

		fTempPositionX += m_fVelocityX * dDt;
		tempRect.x = (int)fTempPositionX;

		//Collision check with tile
		SDL_Rect col;
		const SDL_Rect* pTileRect;

		//Get tile list
		const list<CObject*>* pTileList = CObjMgr::GetInst()->GetObjList(OBJ_GROUNDTILE);

		iterBegin = pTileList->begin();
		iterEnd = pTileList->end();

		for (; iterBegin != iterEnd; ++iterBegin)
		{
			pTileRect = (*iterBegin)->GetDesRect();
			//if ((pTileRect->x + pTileRect->w) > 0 && pTileRect->x < CGame::SCREEN_WIDTH)
			//{
			if (pTileRect->x >= m_desRect.x - 64 && pTileRect->x <= m_desRect.x + 64)
			{
				if (SDL_IntersectRect(&tempRect, pTileRect, &col))
				{
					//Go right
					if (m_fVelocityX > 0)
					{
						m_desRect.x = pTileRect->x - m_desRect.w;
						m_bIsFacingRight = false;
					}
					//Go left
					else
					{
						m_desRect.x = pTileRect->x + pTileRect->w;
						m_bIsFacingRight = true;
					}
					m_fVelocityX = 0;
					m_bCollide = true;
					break;
				}
			}

			// Check for gaps
			if (m_bSafe)
				continue;
			if (pTileRect->y == leftEdge->y)
			{
				if (pTileRect->x >= m_desRect.x - 32 && pTileRect->x <= m_desRect.x + 32)
				{
					m_bSafe = SDL_HasIntersection(m_bIsFacingRight ? rightEdge : leftEdge, pTileRect);
				}
			}
		}

		// Gap detected, turn around
		if (!m_bSafe && !m_bCollide)
		{
			m_bIsFacingRight = !m_bIsFacingRight;
		}
		else
		{
			m_bSafe = false;
			m_bCollide = false;
		}
	}

	// if stunned only move based on tile speed
	m_bIsStunned ? m_fPositionX -= CTile::s_fTileSpeed : m_fPositionX += m_fVelocityX * dDt - CTile::s_fTileSpeed;

	m_desRect.x = (int)m_fPositionX;
	leftEdge->x = (int)m_fPositionX - leftEdge->w;
	rightEdge->x = (int)m_fPositionX + m_desRect.w;



	//Check Vertical collision second
	SDL_Rect tempRect = m_desRect;
	float fTempPositionY = m_fPositionY;

	fTempPositionY += m_fVelocityY * dDt;
	tempRect.y = (int)fTempPositionY;

	//Collision check with tile
	//SDL_Rect col;
	const SDL_Rect* pTileRect;

	//Get tile list
	const list<CObject*>* pTileList = CObjMgr::GetInst()->GetObjList(OBJ_GROUNDTILE);

	//list<CObject*>::const_iterator 
	iterBegin = pTileList->begin();
	//list<CObject*>::const_iterator 
	iterEnd = pTileList->end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pTileRect = (*iterBegin)->GetDesRect();
		//if ((pTileRect->x + pTileRect->w) > 0 && pTileRect->x < CGame::SCREEN_WIDTH)
		//{
		if (pTileRect->x >= m_desRect.x - 32 && pTileRect->x <= m_desRect.x + 32)
		{
			if (SDL_IntersectRect(&tempRect, pTileRect, &col))
			{
				//Go down
				if (m_fVelocityY > 0)
				{
					m_desRect.y = pTileRect->y - m_desRect.h;
				}
				//Go up
				else
				{
					//m_desRect.y = m_desRect.y - (m_desRect.y % pTileRect->h);
					m_desRect.y = pTileRect->y + pTileRect->h;
				}
				m_fVelocityY = 0;
				break;
			}
		}
	}
	m_fPositionY += m_fVelocityY * dDt;
	m_desRect.y = (int)m_fPositionY;
	leftEdge->y = (int)m_fPositionY + m_desRect.h;
	rightEdge->y = (int)m_fPositionY + m_desRect.h;


	//Animation
	if (!m_bIsStunned)
	{
		m_fFrameCtr += dDt * m_fFrameSpeed;

		if (m_fFrameCtr > m_iMoveFrameMax)
			m_fFrameCtr = 0.f;
	}
	else
		m_fFrameCtr = 0;
	//srcRect Update
	m_srcRect.x = floorf(m_fFrameCtr) * m_srcRect.w;



	// If stunned, undo stun after delay
	if (m_bIsStunned)
	{
		m_fStunTick += dDt;

		if (m_fStunTick >= m_fMaxTick)
		{
			m_bIsStunned = false;
			m_fStunTick = 0.0f;
		}
	}

	// If shrunk, undo stun after delay
	if (m_bIsShrunk)
	{
		m_fShrinkTick += dDt;

		if (m_fShrinkTick >= m_fMaxTick)
		{
			m_fPositionY -= m_desRect.h;
			m_desRect.y -= m_desRect.h;

			m_desRect.w *= 2;
			m_desRect.h *= 2;

			m_bIsShrunk = false;
			m_fShrinkTick = 0.0f;
		}
	}
}

void CTurtle::destroyEnemy()
{
	m_bDelete = true;
}

void CTurtle::Render(SDL_Renderer * pRenderer)
{
	if (m_bIsFacingRight == false)
		SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg("Enemy"), &m_srcRect, &m_desRect);
	else
		SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Enemy"), &m_srcRect, &m_desRect, 0, nullptr, SDL_FLIP_HORIZONTAL);

	//SDL_SetRenderDrawColor(pRenderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	//SDL_RenderDrawLine(pRenderer, leftEdge->x, leftEdge->y, leftEdge->x + leftEdge->w, leftEdge->y);    //Left Top -> Right Top
	//SDL_RenderDrawLine(pRenderer, leftEdge->x + leftEdge->w, leftEdge->y, leftEdge->x + leftEdge->w, leftEdge->y + leftEdge->h); //Right Top -> Right Bottom
	//SDL_RenderDrawLine(pRenderer, leftEdge->x + leftEdge->w, leftEdge->y + leftEdge->h, leftEdge->x, leftEdge->y + leftEdge->h); //RIght Bottom -> Left Bottom
	//SDL_RenderDrawLine(pRenderer, leftEdge->x, leftEdge->y + leftEdge->h, leftEdge->x, leftEdge->y); //Left Bottom -> Left Top

	//SDL_RenderDrawLine(pRenderer, rightEdge->x, rightEdge->y, rightEdge->x + rightEdge->w, rightEdge->y);    //Left Top -> Right Top
	//SDL_RenderDrawLine(pRenderer, rightEdge->x + rightEdge->w, rightEdge->y, rightEdge->x + rightEdge->w, rightEdge->y + rightEdge->h); //Right Top -> Right Bottom
	//SDL_RenderDrawLine(pRenderer, rightEdge->x + rightEdge->w, rightEdge->y + rightEdge->h, rightEdge->x, rightEdge->y + rightEdge->h); //RIght Bottom -> Left Bottom
	//SDL_RenderDrawLine(pRenderer, rightEdge->x, rightEdge->y + rightEdge->h, rightEdge->x, rightEdge->y); //Left Bottom -> Left TOp
}

void CTurtle::Shutdown()
{

}
