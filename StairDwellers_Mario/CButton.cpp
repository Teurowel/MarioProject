#include "CButton.h"
#include "CInput.h"

CButton::CButton()
	:m_iFrame(0), m_bClicked(false)
{

}

CButton::CButton(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect)
	:CUI(szImgKey, srcRect, desRect), m_iFrame(0)
{

}

bool CButton::Init()
{
	CUI::Init();



	return true;
}

void CButton::Update(double dDt)
{
	CUI::Update(dDt);

	int iMouseX = CInput::GetInst()->GetMouseX();
	int iMouseY = CInput::GetInst()->GetMouseY();

	//Mouse position rect bound check
	if (iMouseX > m_desRect.x && iMouseX < (m_desRect.x + m_desRect.w) &&
		iMouseY > m_desRect.y && iMouseY < (m_desRect.y + m_desRect.h))
	{
		if (CInput::GetInst()->GetMouseLeft())
			m_bClicked = true;

		m_iFrame = 1;
	}
	else
		m_iFrame = 0;

	m_srcRect.y = m_iFrame * m_srcRect.h;
}

void CButton::Render(SDL_Renderer * pRenderer)
{
	CUI::Render(pRenderer);

}

void CButton::Shutdown()
{
	CUI::Shutdown();
}
