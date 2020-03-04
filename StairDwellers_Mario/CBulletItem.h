#ifndef _CBULLETITEM_H_
#define _CBULLETITEM_H_

#include "CItem.h"

class CBulletItem : public CItem
{
private:
	bulletType m_eBulletType;

public:
	CBulletItem();
	CBulletItem(int iXpos, int iYpos);
	CBulletItem(const CBulletItem& copy) {}
	CBulletItem& operator=(const CBulletItem& copy) {}
	virtual ~CBulletItem() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

public:
	void SetBulletType(bulletType eBulletType);
};

#endif