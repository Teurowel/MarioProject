// Written by: Russell Brabers

#pragma once
#include "CDynamicObject.h"
#include "Enums.h"

#define PROJECTILE_WIDTH 16
#define PROJECTILE_HEIGHT 16

class Projectile : public CDynamicObject
{
public:
	Projectile();
	virtual ~Projectile();

	virtual bool Init();
	virtual void Update(double dDt);
	void Render(SDL_Renderer* pRenderer);
	void Shutdown();

	virtual void setOrientation(const SDL_Rect& source, bool isRight);

	bulletType getBulletType() { return thisBullet; }
	
protected:
	bulletType thisBullet;

	float m_fFireRate = 3;
	float m_fLifeSpan = 12;
};

