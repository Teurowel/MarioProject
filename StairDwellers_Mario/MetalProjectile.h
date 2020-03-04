#pragma once
#include "Projectile.h"

class MetalProjectile : public Projectile
{
public:
	MetalProjectile();
	virtual ~MetalProjectile();
	
	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

private:

};