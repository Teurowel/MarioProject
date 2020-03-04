#pragma once
#include "Projectile.h"

class CMushroomProjectile : public Projectile
{
public:
	CMushroomProjectile();
	virtual ~CMushroomProjectile();

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

private:
	
};

