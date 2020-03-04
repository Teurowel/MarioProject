#pragma once
#include "Projectile.h"

class GhostProjectile : public Projectile
{
public:
	GhostProjectile();
	virtual ~GhostProjectile();
	void setOrientation(const SDL_Rect& source, bool isRight);

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

private:

};