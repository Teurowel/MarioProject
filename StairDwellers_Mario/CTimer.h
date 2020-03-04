/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//timer class is the representation of frame of our class
//It will be used to check tick, our game is updated and rendered based on this tick
*//////////////////////////////////////////////////////////////////////

#ifndef _CTIMER_H_
#define _CTIMER_H_

#define FPS 60

#include <chrono>
#include "SingletonDefines.h"
using namespace std;
using namespace chrono;

class CTimer
{
	DECLARE_SINGLETON(CTimer)
private :
	double m_dSecondsPerCount;
	double m_dDeltaTime;	//in second

	__int64 m_iCurrCount;	//We will get count from CPU i guess not time, we convert count to time(second)
	__int64 m_iPrevCount;

public :
	bool Init();
	void Shutdown();

	double GetDeltaTime();

};

#endif