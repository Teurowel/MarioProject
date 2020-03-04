#include "MetalProjectile.h"
#include "CImgMgr.h"
#include "CGame.h"
#include "CObjMgr.h"
#include "CTimer.h"
#include "CTile.h"

MetalProjectile::MetalProjectile()
{
}

MetalProjectile::~MetalProjectile()
{
}

bool MetalProjectile::Init()
{
	thisBullet = bulletType::METAL;

	m_srcRect.x = 16 * 3;
	m_srcRect.y = 0;
	m_srcRect.w = PROJECTILE_WIDTH;
	m_srcRect.h = PROJECTILE_HEIGHT;

	m_desRect.w = PROJECTILE_WIDTH;
	m_desRect.h = PROJECTILE_HEIGHT;

	return true;
}

void MetalProjectile::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopyEx(pRenderer, CImgMgr::GetInst()->GetImg("Bullets"), &m_srcRect, &m_desRect, 10, nullptr, m_bIsFacingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void MetalProjectile::Update(double deltatime)
{
	Projectile::Update(deltatime);
}

void MetalProjectile::Shutdown()
{

}
