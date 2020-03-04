#include "CCoinScoreFont.h"

#include "CObjMgr.h"
#include "CPlayer.h"
#include "CCoinItem.h"
#include <string>
#include <sstream>

CCoinScoreFont::CCoinScoreFont()
{

}

CCoinScoreFont::CCoinScoreFont(string szString, SDL_Color fontColor, int iX, int iY)
	: CFont(szString, fontColor, iX, iY)
{
	m_coinSrcRect.x = 0;
	m_coinSrcRect.y = 0;
	m_coinSrcRect.w = COINWIDTH;
	m_coinSrcRect.h = COINHEIGHT;

	m_coindDesRect.x = iX - 20;
	m_coindDesRect.y = iY + 5;
	m_coindDesRect.w = 16;
	m_coindDesRect.h = 16;
}

bool CCoinScoreFont::Init()
{
	CFont::Init();

	return true;
}

void CCoinScoreFont::Update(double dDt)
{
	CObject* pPlayer = CObjMgr::GetInst()->GetObj(OBJ_PLAYER);
	
	m_szString = to_string(((CPlayer*)pPlayer)->GetCoinScore());

	CFont::Update(dDt);
}

void CCoinScoreFont::Render(SDL_Renderer * pRenderer)
{
	CFont::Render(pRenderer);

	//Coin image
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg("Coin"), &m_coinSrcRect, &m_coindDesRect);
}

void CCoinScoreFont::Shutdown()
{



	CFont::Shutdown();
}
