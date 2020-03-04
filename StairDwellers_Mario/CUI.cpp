#include "CUI.h"
#include "CImgMgr.h"

CUI::CUI()
{

}

CUI::CUI(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect)
	:m_szImgKey(szImgKey)
{
	m_srcRect = srcRect;

	m_desRect = desRect;
}


bool CUI::Init()
{

	return true;
}

void CUI::Update(double dDt)
{
}

void CUI::Render(SDL_Renderer * pRenderer)
{
	//system("CLS");
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg(m_szImgKey), &m_srcRect, &m_desRect);
}

void CUI::Shutdown()
{
}
