#ifndef _CGAMESTATE_H_
#define _CGAMESTATE_H_

#include "CState.h"

class Player;
class CGameState : public CState
{
public :
	static const int MAX_LEVEL = 4;
	enum sfx {Item, Transition};

private :

public:
	CGameState();
	virtual ~CGameState();

	virtual bool Init();
	virtual void Update(double dDt); // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Shutdown();

private :
	void CreateObject();	//Create all objects for game
	void CreateMap();		//Create Map tiles
};

#endif