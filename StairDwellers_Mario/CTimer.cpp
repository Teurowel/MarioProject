#include "CTimer.h"

//do this to speed up the build process, it reduces the size of the Win32 header files by excluding some of the less used APIs.
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

IMPLEMENT_SINGLETON(CTimer)

CTimer::CTimer()
	:m_dSecondsPerCount(0)
{

}

bool CTimer::Init()
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);	//Get Counts per Second
	m_dSecondsPerCount = 1.0 / (double)countsPerSec;				//Calculate Seconds Per Count

	//Get Count
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iCurrCount);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iPrevCount);

	return true;
}

void CTimer::Shutdown()
{

}

//return DeltaTime in second
double CTimer::GetDeltaTime()
{
	m_iPrevCount = m_iCurrCount; //For next frame calculate
	
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iCurrCount);		//Get Current time value in Count

	//Calculate elapsed Count between last frame and current frmae. 
	//Once we get elapsed Count, we multiply SecondsPerCount to convert Count to Second
	m_dDeltaTime = (m_iCurrCount - m_iPrevCount) * m_dSecondsPerCount;	

	if (m_dDeltaTime > 0.01)
		m_dDeltaTime = 0.01;

	return m_dDeltaTime;													
}