#include "GoldProjectile.h"
#include "CTile.h"
#include "CImgMgr.h"
#include "CGame.h"

GoldProjectile::GoldProjectile()
{
}

GoldProjectile::~GoldProjectile()
{
}

bool GoldProjectile::Init()
{
	thisBullet = bulletType::GOLD;

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 104;
	m_srcRect.h = 107;

	m_desRect.w = 35;
	m_desRect.h = 35;

	m_fVelocityY = 100;

	return true;
}

void GoldProjectile::setOrientation(const SDL_Rect& source, bool isRight)
{
	m_desRect.y = source.y - 60;
	m_desRect.x = source.x;
	m_fPositionX = m_desRect.x;
	m_fPositionY = m_desRect.y;
	//m_bIsFacingRight = isRight;
	//m_fPositionX = m_bIsFacingRight ? source.x + source.w : source.x + m_srcRect.w;
	//m_desRect.x = (int)m_fPositionX;

	//m_fPositionY = source.y + source.h * 0.5;
	//m_desRect.y = (int)m_fPositionY;

}

void GoldProjectile::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("GoldMushroom"), &m_srcRect, &m_desRect, 0, nullptr, SDL_FLIP_NONE);
}

void GoldProjectile::Update(double deltatime)
{
	m_fPositionY += m_fVelocityY * deltatime;
	m_desRect.y = (int)m_fPositionY;

	m_fPositionX += m_fVelocityX * deltatime - CTile::s_fTileSpeed;
	m_desRect.x = (int)m_fPositionX;
}

void GoldProjectile::Shutdown()
{

}
