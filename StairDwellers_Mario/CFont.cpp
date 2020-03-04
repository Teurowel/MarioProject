#include "CFont.h"

#include "SDL_ttf.h"
#include "CGame.h"

CFont::CFont()
	:m_szString(""), m_szPrevString(""), m_pFontSurface(nullptr), m_pFontTexture(nullptr), m_dMaxExistTime(0), m_dExistTime(0)
{

}

CFont::CFont(string szString, SDL_Color fontColor, int iX, int iY, double dMaxExistTime)
	:m_szString(szString), m_szPrevString(""), m_FontColor(fontColor), m_dMaxExistTime(dMaxExistTime), m_dExistTime(0)
{
	m_rFontRect.x = iX;
	m_rFontRect.y = iY;
}

bool CFont::Init()
{
	return true;
}

void CFont::Update(double dDt)
{
	if (m_dMaxExistTime != 0)
	{
		m_dExistTime += dDt;

		if (m_dExistTime >= m_dMaxExistTime)
			m_bDelete = true;
	}

	if (m_szString != m_szPrevString)
	{
		m_szPrevString = m_szString;
		SDL_FreeSurface(m_pFontSurface);
		SDL_DestroyTexture(m_pFontTexture);

		m_pFontSurface = TTF_RenderText_Solid(CGame::GetInst()->GetFont(), m_szString.c_str(), m_FontColor);
		m_pFontTexture = SDL_CreateTextureFromSurface(CGame::GetInst()->GetRenderer(), m_pFontSurface);
		m_rFontRect.w = m_pFontSurface->w;
		m_rFontRect.h = m_pFontSurface->h;
	}

	//m_szString = "SHIPS:dddddddddddddddddddd ";// +to_string((int)m_pPlayers.size()); // Getting player vector size.
}

void CFont::Render(SDL_Renderer * pRenderer)
{
	// Update ship counter text.
	SDL_RenderCopy(pRenderer, m_pFontTexture, 0, &m_rFontRect);
}

void CFont::Shutdown()
{
	SDL_FreeSurface(m_pFontSurface);
	SDL_DestroyTexture(m_pFontTexture);
}
