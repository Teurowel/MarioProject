#ifndef _CTITLESTATE_H_
#define _CTITLESTATE_H_

#include "CState.h"
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

class Button;
class CTitleState : public CState
{
public :
	enum btn { play, exit };

public:
	CTitleState();
	virtual ~CTitleState();

public :
	virtual bool Init();
	virtual void Update(double dDt); // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Shutdown();
};

#endif