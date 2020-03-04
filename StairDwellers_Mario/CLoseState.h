#ifndef _CLOSESTATE_H_
#define _CLOSESTATE_H_

#include "CState.h"
#include <vector>
#include <SDL_image.h>
using namespace std;

class Button;
class CLoseState : public CState
{
public:
	enum btn { mainmenu };

public:
	CLoseState();
	virtual ~CLoseState();

public:
	virtual bool Init();
	virtual void Update(double dDt); // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Shutdown();
};

#endif