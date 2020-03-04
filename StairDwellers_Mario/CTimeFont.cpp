#include "CTimeFont.h"

#include <string>
#include <sstream>

CTimeFont::CTimeFont()
	:m_dAccumulatedTime(0)
{

}

CTimeFont::CTimeFont(string szString, SDL_Color fontColor, int iX, int iY)
	:CFont(szString, fontColor, iX, iY), m_dAccumulatedTime(0)
{

}

bool CTimeFont::Init()
{
	CFont::Init();

	return true;
}

void CTimeFont::Update(double dDt)
{
	m_dAccumulatedTime += dDt;

	std::ostringstream out;
	out.precision(0);
	out << std::fixed << m_dAccumulatedTime;

	m_szString = "Time: " + out.str();

	CFont::Update(dDt);
}

void CTimeFont::Render(SDL_Renderer * pRenderer)
{
	CFont::Render(pRenderer);
}

void CTimeFont::Shutdown()
{



	CFont::Shutdown();
}
