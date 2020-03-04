#include "GhostProjectile.h"
#include "CTile.h"
#include "CImgMgr.h"
#include "CGame.h"

GhostProjectile::GhostProjectile()
{
}

GhostProjectile::~GhostProjectile()
{
}

bool GhostProjectile::Init()
{
	thisBullet = bulletType::GHOST;

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 104;
	m_srcRect.h = 107;

	m_desRect.w = 35;
	m_desRect.h = 35;

	m_fVelocityY = 100;

	return true;
}

void GhostProjectile::setOrientation(const SDL_Rect& source, bool isRight)
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

void GhostProjectile::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Ghost"), &m_srcRect, &m_desRect, 0, nullptr, SDL_FLIP_NONE);
}

void GhostProjectile::Update(double deltatime)
{
	m_fPositionY += m_fVelocityY * deltatime - CTile::s_fTileSpeed;
	m_desRect.y = (int)m_fPositionY;
}

void GhostProjectile::Shutdown()
{

}