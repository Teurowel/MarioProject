#pragma once
#include "Projectile.h"

class FireBullet :public Projectile
{
private:
	float m_fSpeed = 5;
	//float m_fFireRate = 3;
	//float m_fLifeSpan = 12;
	int m_fAngle = 0;

	float m_fAnimCnt, m_fAnimMax;
public:
	FireBullet();
	~FireBullet();

	void setOrientation(const SDL_Rect&, bool);
	void Render(SDL_Renderer* pRenderer);
	void Update(double deltatime);
	bool Init();
	void spawnNewBullet(int angle, int velocityX);
};