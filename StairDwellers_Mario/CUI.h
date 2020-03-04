#ifndef _CUI_H_
#define _CUI_H_

#include "CStaticObject.h"

class CUI : public CStaticObject
{
private :
	const char* m_szImgKey;

public:
	CUI();
	CUI(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect);
	CUI(const CUI& copy) {}
	CUI& operator=(const CUI& copy) {}
	virtual ~CUI() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();
};

#endif