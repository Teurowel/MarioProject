#include "CTitleBackGround.h"
#include "CGame.h"
#include "CImgMgr.h"

CTitleBackGround::CTitleBackGround()
	:m_szImgKey(nullptr)
{

}

CTitleBackGround::CTitleBackGround(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect)
	:m_szImgKey(szImgKey)
{
	m_srcRect = srcRect;
	m_desRect = desRect;
}

bool CTitleBackGround::Init()
{
	//Set First background
	m_fPositionX = 0.f;
	m_desRect.x = (int)m_fPositionX;

	m_fPositionY = 0.f;
	m_desRect.y = (int)m_fPositionY;

	m_desRect.w = CGame::SCREEN_WIDTH;
	m_desRect.h = CGame::SCREEN_HEIGHT;


	return true;
}

void CTitleBackGround::Update(double dDt)
{

}

void CTitleBackGround::Render(SDL_Renderer* pRenderer)
{
	//First background
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg(m_szImgKey), &m_srcRect, &m_desRect);
}

void CTitleBackGround::Shutdown()
{

}