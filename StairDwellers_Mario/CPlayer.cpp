#include "CPlayer.h"
#include "CObjMgr.h"
#include "Projectile.h"
#include "CGame.h"
#include "CTile.h"
#include "CEnemy.h"
#include "CAudioMgr.h"
#include "CMushroomProjectile.h"
#include "MetalProjectile.h"
#include "FireBullet.h"
#include "CState.h"
#include "CStateMgr.h"
#include "CUI.h"
#include "CFactory.h"

CPlayer::CPlayer()
{

}

bool CPlayer::Init()
{
	m_iHealth = 3;

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = PLAYER_WIDTH;
	m_srcRect.h = PLAYER_HEIGHT;

	m_fPositionX = 16 * 18;
	m_desRect.x = (int)m_fPositionX;

	m_fPositionY = 16 * 17;
	m_desRect.y = (int)m_fPositionY;
	m_desRect.w = PLAYER_WIDTH * 2;
	m_desRect.h = PLAYER_HEIGHT * 2;

	m_fSpeed = 225.f;
	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;

	m_bJump = false;
	m_bHasFired = false;
	m_bIsFacingRight = false;
	m_bIsHit = false;
	m_bIsTransit = false;
	m_bIsInvincible = false;

	m_fInvcCnt = 0;
	m_fInvcMax = 2;
	
	m_fFlashCnt = 0;
	m_fFlashMax = 0.1f;

	m_fFrameSpeed = 10.f;
	m_iMoveFrameMax = 3;

	currentBullet = bulletType::DEFAULT;

	return true;
}

void CPlayer::Update(double dDt)
{
	//Call parent class's update first
	CDynamicObject::Update(dDt);

	if (m_bIsTransit == false)
	{
		if (!m_bDelete && !m_bIsHit && CInput::GetInst()->KeyDown(SDL_SCANCODE_A))
		{
			m_fVelocityX = -m_fSpeed;
			m_bIsFacingRight = false;
		}
		else if (!m_bDelete && !m_bIsHit && CInput::GetInst()->KeyDown(SDL_SCANCODE_D))
		{
			m_fVelocityX = m_fSpeed;
			m_bIsFacingRight = true;
		}
		else
		{
			if (m_fVelocityX > 0)
				m_fVelocityX -= m_fSpeed / 50;
			else if (m_fVelocityX < 0)
				m_fVelocityX += m_fSpeed / 50;
			//m_fVelocityX = 0.f;
		}


		if (!m_bDelete && !m_bIsHit && CInput::GetInst()->KeyDown(SDL_SCANCODE_W))
		{
			if (m_bJump == false)
			{
				m_fVelocityY = -400.f;
				m_bJump = true;
				CAudioMgr::GetInst()->PlaySound("Jump");
			}
		}
	}

	//Check vertical collision first
	if (m_fVelocityX != 0)
	{
		//Make Temp rect and position for collision
		SDL_Rect tempRect = m_desRect;
		float fTempPositionX = m_fPositionX;

		fTempPositionX += m_fVelocityX * dDt;
		tempRect.x = (int)fTempPositionX;

		if (tempRect.x <= 0)
		{
			m_desRect.x = 0;
			m_fVelocityX = 0;
		}
		else
		{
			//Collision check with tile
			SDL_Rect col;
			const SDL_Rect* pTileRect;

			//Get tile list
			const list<CObject*>* pTileList = CObjMgr::GetInst()->GetObjList(OBJ_GROUNDTILE);

			list<CObject*>::const_iterator iterBegin = pTileList->begin();
			list<CObject*>::const_iterator iterEnd = pTileList->end();

			for (; iterBegin != iterEnd; ++iterBegin)
			{
				pTileRect = (*iterBegin)->GetDesRect();

				//CHeck if tile is in screen
				if ((pTileRect->x + pTileRect->w) > 0 && pTileRect->x < CGame::SCREEN_WIDTH)
				{
					if (SDL_IntersectRect(&tempRect, pTileRect, &col))
					{
						//Go right
						if (m_fVelocityX > 0)
						{
							m_desRect.x = pTileRect->x - m_desRect.w;
						}
						//Go left
						else
						{
							m_desRect.x = pTileRect->x + pTileRect->w;
						}
						m_fVelocityX = 0;
						break;
					}
				}
			}
		}
	}


	if (m_fPositionX < CGame::SCREEN_WIDTH * 0.5 || m_fVelocityX < 0)
	{
		m_fPositionX += m_fVelocityX * dDt;
		m_desRect.x = (int)m_fPositionX;
	}


	//Check horizontal collision second
	SDL_Rect tempRect = m_desRect;
	float fTempPositionY = m_fPositionY;

	fTempPositionY += m_fVelocityY * dDt;
	tempRect.y = (int)fTempPositionY;

	//Collision check with tile
	SDL_Rect col;
	const SDL_Rect* pTileRect;

	//Get tile list
	const list<CObject*>* pTileList = CObjMgr::GetInst()->GetObjList(OBJ_GROUNDTILE);

	list<CObject*>::const_iterator iterBegin = pTileList->begin();
	list<CObject*>::const_iterator iterEnd = pTileList->end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pTileRect = (*iterBegin)->GetDesRect();

		//CHeck if tile is in screen
		if ((pTileRect->x + pTileRect->w) > 0 && pTileRect->x < CGame::SCREEN_WIDTH)
		{
			if (SDL_IntersectRect(&tempRect, pTileRect, &col))
			{
				//Go down
				if (m_fVelocityY > 0)
				{
					m_desRect.y = pTileRect->y - m_desRect.h;
					m_bJump = false;
					m_bIsHit = false;
				}
				//Go up
				else
				{
					m_desRect.y = pTileRect->y + pTileRect->h;
				}
				m_fVelocityY = 0;
				break;
			}
			else
				m_bJump = true;
		}
	}

	m_fPositionY += m_fVelocityY * dDt;
	m_desRect.y = (int)m_fPositionY;

	// Collision with enemies and bullets
	const SDL_Rect* nmeRect;
	SDL_Rect pCenter, eCenter;
	SDL_Rect pVec, eVec;
	int crossProd;

	//Get Enemy list
	const list<CObject*>* pNmeList = CObjMgr::GetInst()->GetObjList(OBJ_ENEMY);
	if (!m_bIsInvincible)
	{
		for (list<CObject*>::const_iterator iterBegin = pNmeList->begin(); iterBegin != pNmeList->end(); iterBegin++)
		{
			nmeRect = (*iterBegin)->GetDesRect();

			if (!m_bDelete && SDL_IntersectRect(&m_desRect, nmeRect, &col))
			{
				CEnemy* nme = (CEnemy*)(*iterBegin);

				pCenter.x = m_desRect.x + m_desRect.w / 2;
				pCenter.y = m_desRect.y + m_desRect.h / 2;

				eCenter.x = nmeRect->x + nmeRect->w / 2;
				eCenter.y = nmeRect->y + nmeRect->h / 2;

				pVec.x = pCenter.x - eCenter.x;
				pVec.y = pCenter.y - eCenter.y;

				eVec.y = nmeRect->y - eCenter.y;

				// Player is to the left of the enemy
				if (pCenter.x < eCenter.x)
				{
					eVec.x = nmeRect->x - eCenter.x;

					crossProd = (pVec.x * eVec.y) - (pVec.y * eVec.x);

					if (crossProd > 0)
					{
						m_iHealth -= 1;
						CGame::GetInst()->m_hp -= 1;
						m_bIsHit = true;
						m_bIsInvincible = true;
						m_fVelocityY = -150.f;
						m_fVelocityX = -400.f;
						CAudioMgr::GetInst()->PlaySound("Hurt");
					}
					else
					{
						if (!nme->m_bIsShrunk)
						{
							nme->m_bIsStunned = true;
							m_fVelocityY = -200.f;
						}
						else
						{
							m_fVelocityY = -100.0f;
							nme->destroyEnemy();
						}
						CAudioMgr::GetInst()->PlaySound("Stomp");
					}
				}
				// Player is centered or to the right
				else
				{
					eVec.x = (nmeRect->x + nmeRect->w) - eCenter.x;

					crossProd = (pVec.x * eVec.y) - (pVec.y * eVec.x);

					if (crossProd < 0)
					{
						m_iHealth -= 1;
						m_bIsHit = true;
						m_bIsInvincible = true;
						m_fVelocityY = -150.f;
						m_fVelocityX = 400.f;
						CAudioMgr::GetInst()->PlaySound("Hurt");
					}
					else
					{
						if (!nme->m_bIsShrunk)
						{
							nme->m_bIsStunned = true;
							m_fVelocityY = -200.f;
						}
						else
						{
							m_fVelocityY = -100.0f;
							nme->destroyEnemy();
						}
						CAudioMgr::GetInst()->PlaySound("Stomp");
					}
				}
			}
		}

		Projectile* bullet = dynamic_cast<Projectile*>(checkBulletCollision());
		if (bullet != nullptr)
		{
			m_iHealth -= 1;
			m_bIsHit = true;
			m_bIsInvincible = true;
			m_fVelocityY = -150.f;
			m_fVelocityX = bullet->GetDesRect()->x < GetDesRect()->x ? 400.f : -400.f;
			CAudioMgr::GetInst()->PlaySound("Hurt");
			bullet->SetDelete(true);
		}
	}


	//Jump
	if (m_fVelocityY < 0.f)
	{
		m_fFrameCtr = 3.f;
	}	

	else if (m_fVelocityY > 0.f)
	{
		m_fFrameCtr = 4.f;
	}

	//Animation
	//else if (CInput::GetInst()->KeyDown(SDL_SCANCODE_A) || CInput::GetInst()->KeyDown(SDL_SCANCODE_D))
	else if(m_fVelocityX > 0 || m_fVelocityX < 0)
	{
		m_fFrameCtr += dDt * m_fFrameSpeed;

		if (m_fFrameCtr > m_iMoveFrameMax)
			m_fFrameCtr = 0.f;
	}

	//Idle
	else
	{
		m_fFrameCtr = 0;
	}

	//srcRect Update
	m_srcRect.x = floorf(m_fFrameCtr) * PLAYER_WIDTH;

	if (CInput::GetInst()->KeyDown(SDL_SCANCODE_Z))
	{
		currentBullet = bulletType::DEFAULT;
		CObjMgr::GetInst()->GetObj(OBJ_UI)->SetSrcRect(0, 0, 16, 16);
	}
	if (CInput::GetInst()->KeyDown(SDL_SCANCODE_X))
	{
		currentBullet = bulletType::FIRE;
		CObjMgr::GetInst()->GetObj(OBJ_UI)->SetSrcRect(16, 0, 16, 16);
	}
	if (CInput::GetInst()->KeyDown(SDL_SCANCODE_C))
	{
		currentBullet = bulletType::SHRINK;
		CObjMgr::GetInst()->GetObj(OBJ_UI)->SetSrcRect(32, 0, 16, 16);
	}
	if (CInput::GetInst()->KeyDown(SDL_SCANCODE_V))
	{
		currentBullet = bulletType::METAL;
		CObjMgr::GetInst()->GetObj(OBJ_UI)->SetSrcRect(48, 0, 16, 16);
	}
	//Create Bullet
	if (!m_bDelete && !m_bIsHit && CInput::GetInst()->KeyDown(SDL_SCANCODE_SPACE))
	{
		if (m_bHasFired == false)
		{
			Projectile* pProjectile;
			switch (currentBullet)
			{
			case FIRE: 
				pProjectile = new FireBullet;
				break;
			case SHRINK:
				pProjectile = new CMushroomProjectile;
				break;
			case METAL:
				pProjectile = new MetalProjectile;
				break;
			default:
				pProjectile = new Projectile;
				break;
			}
			m_bHasFired = true;
			// Projectile* pProjectile = new Projectile;
			pProjectile->Init();
			pProjectile->setOrientation(m_desRect, m_bIsFacingRight);
			CObjMgr::GetInst()->AddObj(pProjectile, OBJ_BULLET);
			CAudioMgr::GetInst()->PlaySound("Bullet");
		}
	}	
	else
		m_bHasFired = false;

	if (m_bIsInvincible)
	{
		if (m_fInvcCnt >= m_fInvcMax)
		{
			m_bIsInvincible = false;
			m_fInvcCnt = 0;
		}
		else
			m_fInvcCnt += dDt;

		if (m_fFlashCnt >= m_fFlashMax * 2)
			m_fFlashCnt = 0;
		else
			m_fFlashCnt += dDt;
	}

	if (m_iHealth <= 0 || m_fPositionY >= CGame::SCREEN_HEIGHT)
	{
		m_bDelete = true;
		CGame::GetInst()->GetStateMgr()->SetState(CStateMgr::STATE_LOSE);
	}
}

void CPlayer::Render(SDL_Renderer* pRenderer)
{
	if (m_bIsInvincible)
	{
		if (m_fFlashCnt < m_fFlashMax)
		{
			if (m_bIsFacingRight)
				SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Mario"), &m_srcRect, &m_desRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
			else
				SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg("Mario"), &m_srcRect, &m_desRect);
		}
	}
	else
	{
		if (m_bIsFacingRight)
			SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Mario"), &m_srcRect, &m_desRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg("Mario"), &m_srcRect, &m_desRect);
	}
}

void CPlayer::Shutdown()
{

}