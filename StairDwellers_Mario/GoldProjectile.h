#pragma once
#include "Projectile.h"

class GoldProjectile : public Projectile
{
public:
	GoldProjectile();
	virtual ~GoldProjectile();
	void setOrientation(const SDL_Rect& source, bool isRight);

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

private:

};