#pragma once
#include "CState.h"
#include <vector>
#include <SDL_image.h>

class Button;

class CPauseState : public CState
{
	enum btn { mainmenu };
	//enum btn { Continue };

private :
	CObject* pPauseBackGround;
	CObject* pContinueButton;

public:
	CPauseState();
	~CPauseState();

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render();
	virtual void Shutdown();
};

