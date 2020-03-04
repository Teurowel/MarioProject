#ifndef _CWINSTATE_H_
#define _CWINSTATE_H_

#include "CState.h"
#include <vector>
#include <SDL_image.h>
using namespace std;

class Button;
class CWinState : public CState
{
public:
	enum btn { mainmenu };

public:
	CWinState();
	virtual ~CWinState();

public:
	virtual bool Init();
	virtual void Update(double dDt); // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Shutdown();
};

#endif