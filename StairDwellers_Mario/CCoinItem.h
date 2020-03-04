#ifndef _CCOINITEM_H_
#define _CCOINITEM_H_

#include "CItem.h"

#define COINWIDTH 95
#define COINHEIGHT 97

class CCoinItem : public CItem
{
public:
	CCoinItem();
	CCoinItem(int iXpos, int iYpos);
	CCoinItem(const CCoinItem& copy) {}
	CCoinItem& operator=(const CCoinItem& copy) {}
	virtual ~CCoinItem() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

};

#endif