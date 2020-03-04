#include "CMushroomProjectile.h"
#include "CImgMgr.h"
#include "CGame.h"
#include "CTile.h"
#include "CInput.h"
#include "CObjMgr.h"
#include "CAudioMgr.h"

bool m_bIsHit = false;
bool m_bHasFired = false;
CMushroomProjectile::CMushroomProjectile()
{
}

CMushroomProjectile::~CMushroomProjectile()
{
}

bool CMushroomProjectile::Init()
{
	thisBullet = bulletType::SHRINK;

	m_srcRect.x = 32;
	m_srcRect.y = 0;
	m_srcRect.w = PROJECTILE_WIDTH;
	m_srcRect.h = PROJECTILE_HEIGHT;

	m_desRect.w = PROJECTILE_WIDTH;
	m_desRect.h = PROJECTILE_HEIGHT;

	return true;
}

void CMushroomProjectile::Update(double dDt)
{
	Projectile::Update(dDt);
}

void CMushroomProjectile::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Bullets"), &m_srcRect, &m_desRect, 0, nullptr, m_bIsFacingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void CMushroomProjectile::Shutdown()
{

}