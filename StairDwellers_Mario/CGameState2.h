#ifndef _CGAMESTATE2_H_
#define _CGAMESTATE2_H_

#include "CState.h"

class CGameState2 : public CState
{

public:
	CGameState2();
	virtual ~CGameState2();

	virtual bool Init();
	virtual void Update(double dDt); // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Shutdown();

private:
	void CreateObject();	//Create all objects for game
	void CreateMap();		//Create Map tiles
};

#endif
