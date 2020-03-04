#ifndef _CBUTTON_H
#define _CBUTTON_H

#include "CUI.h"

class CButton : public CUI
{
private :
	int m_iFrame;

	bool m_bClicked;

public :
	CButton();
	CButton(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect);
	CButton(const CButton & copy) {}
	CButton & operator=(const CButton & copy) {}
	virtual ~CButton() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();
	



	//simple getter setter
public :
	bool GetClicked() const { return m_bClicked; }
};

#endif