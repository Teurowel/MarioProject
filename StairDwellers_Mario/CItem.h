#ifndef _CITEM_H_
#define _CITEM_H_

#include "CStaticObject.h"
#include "Projectile.h"

class CItem : public CStaticObject
{
private :
	bulletType m_eBulletType;

public:
	CItem();
	CItem(int iXpos, int iYpos);
	CItem(const CItem& copy) {}
	CItem& operator=(const CItem& copy) {}
	virtual ~CItem() {}

	virtual bool Init() = 0;
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer) = 0;
	virtual void Shutdown() = 0;

public :
	void SetBulletType(bulletType eBulletType);
};

#endif