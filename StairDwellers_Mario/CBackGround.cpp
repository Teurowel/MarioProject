#include "CBackGround.h"
#include "CGame.h"
#include "CTile.h"

CBackGround::CBackGround()
{

}

CBackGround::CBackGround(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect)
	:m_szImgKey(szImgKey)
{
	m_srcRect = srcRect;
	m_desRect = desRect;
}

bool CBackGround::Init()
{
	//Set First background
	m_fPositionX = 0.f;
	m_desRect.x = (int)m_fPositionX;

	m_fPositionY = 0.f;
	m_desRect.y = (int)m_fPositionY;

	m_desRect.w = CGame::SCREEN_WIDTH;
	m_desRect.h = CGame::SCREEN_HEIGHT;

	//Set second backghround
	m_fSecondPositionX = m_desRect.w;
	m_SecondDesRect = m_desRect;
	m_SecondDesRect.x = m_fSecondPositionX;
	
	return true;
}

void CBackGround::Update(double dDt)
{
	m_fPositionX -= CTile::s_fTileSpeed;
	m_desRect.x = (int)m_fPositionX;

	//Move First background to right side
	if (m_fPositionX + m_desRect.w < 0)
	{
		m_fPositionX = m_desRect.w;
		m_desRect.x = (int)m_fPositionX;
	}

	m_fSecondPositionX -= CTile::s_fTileSpeed;
	m_SecondDesRect.x = (int)m_fSecondPositionX;

	//Move Second Backgroudn to right side
	if (m_fSecondPositionX + m_desRect.w < 0)
	{
		m_fSecondPositionX = m_desRect.w;
		m_SecondDesRect.x = (int)m_fSecondPositionX;
	}
}

void CBackGround::Render(SDL_Renderer* pRenderer)
{
	//First background
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg(m_szImgKey), &m_srcRect, &m_desRect);

	//Second background
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg(m_szImgKey), &m_srcRect, &m_SecondDesRect);
}

void CBackGround::Shutdown()
{
	
}